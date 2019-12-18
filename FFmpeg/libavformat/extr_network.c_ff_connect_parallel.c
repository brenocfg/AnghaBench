#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int fd; int deadline_us; TYPE_1__* addr; scalar_t__ revents; int /*<<< orphan*/  events; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; } ;
struct ConnectionAttempt {int fd; int deadline_us; TYPE_1__* addr; scalar_t__ revents; int /*<<< orphan*/  events; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  portbuf ;
typedef  int /*<<< orphan*/  last_err ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  hostbuf ;
typedef  int /*<<< orphan*/  errbuf ;
struct TYPE_8__ {char* filename; int /*<<< orphan*/  interrupt_callback; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_7__ {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; } ;

/* Variables and functions */
 int AVERROR (int) ; 
 int AVERROR_EXIT ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int ECONNREFUSED ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int FFMIN (int,int) ; 
 int FF_ARRAY_ELEMS (struct pollfd*) ; 
 int NEXT_ATTEMPT_DELAY_MS ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 scalar_t__ av_gettime_relative () ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  av_strerror (int,char*,int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int ff_neterrno () ; 
 int ff_poll_interrupt (struct pollfd*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getnameinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  interleave_addrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  memmove (struct pollfd*,struct pollfd*,int) ; 
 int /*<<< orphan*/  print_address_list (TYPE_2__*,struct addrinfo*,char*) ; 
 int start_connect_attempt (struct pollfd*,struct addrinfo**,int,TYPE_2__*,void (*) (void*,int),void*) ; 

int ff_connect_parallel(struct addrinfo *addrs, int timeout_ms_per_address,
                        int parallel, URLContext *h, int *fd,
                        void (*customize_fd)(void *, int), void *customize_ctx)
{
    struct ConnectionAttempt attempts[3];
    struct pollfd pfd[3];
    int nb_attempts = 0, i, j;
    int64_t next_attempt_us = av_gettime_relative(), next_deadline_us;
    int last_err = AVERROR(EIO);
    socklen_t optlen;
    char errbuf[100], hostbuf[100], portbuf[20];

    if (parallel > FF_ARRAY_ELEMS(attempts))
        parallel = FF_ARRAY_ELEMS(attempts);

    print_address_list(h, addrs, "Original list of addresses");
    // This mutates the list, but the head of the list is still the same
    // element, so the caller, who owns the list, doesn't need to get
    // an updated pointer.
    interleave_addrinfo(addrs);
    print_address_list(h, addrs, "Interleaved list of addresses");

    while (nb_attempts > 0 || addrs) {
        // Start a new connection attempt, if possible.
        if (nb_attempts < parallel && addrs) {
            getnameinfo(addrs->ai_addr, addrs->ai_addrlen,
                        hostbuf, sizeof(hostbuf), portbuf, sizeof(portbuf),
                        NI_NUMERICHOST | NI_NUMERICSERV);
            av_log(h, AV_LOG_VERBOSE, "Starting connection attempt to %s port %s\n",
                                      hostbuf, portbuf);
            last_err = start_connect_attempt(&attempts[nb_attempts], &addrs,
                                             timeout_ms_per_address, h,
                                             customize_fd, customize_ctx);
            if (last_err < 0) {
                av_strerror(last_err, errbuf, sizeof(errbuf));
                av_log(h, AV_LOG_VERBOSE, "Connected attempt failed: %s\n",
                                          errbuf);
                continue;
            }
            if (last_err > 0) {
                for (i = 0; i < nb_attempts; i++)
                    closesocket(attempts[i].fd);
                *fd = attempts[nb_attempts].fd;
                return 0;
            }
            pfd[nb_attempts].fd = attempts[nb_attempts].fd;
            pfd[nb_attempts].events = POLLOUT;
            next_attempt_us = av_gettime_relative() + NEXT_ATTEMPT_DELAY_MS * 1000;
            nb_attempts++;
        }

        av_assert0(nb_attempts > 0);
        // The connection attempts are sorted from oldest to newest, so the
        // first one will have the earliest deadline.
        next_deadline_us = attempts[0].deadline_us;
        // If we can start another attempt in parallel, wait until that time.
        if (nb_attempts < parallel && addrs)
            next_deadline_us = FFMIN(next_deadline_us, next_attempt_us);
        last_err = ff_poll_interrupt(pfd, nb_attempts,
                                     (next_deadline_us - av_gettime_relative())/1000,
                                     &h->interrupt_callback);
        if (last_err < 0 && last_err != AVERROR(ETIMEDOUT))
            break;

        // Check the status from the poll output.
        for (i = 0; i < nb_attempts; i++) {
            last_err = 0;
            if (pfd[i].revents) {
                // Some sort of action for this socket, check its status (either
                // a successful connection or an error).
                optlen = sizeof(last_err);
                if (getsockopt(attempts[i].fd, SOL_SOCKET, SO_ERROR, &last_err, &optlen))
                    last_err = ff_neterrno();
                else if (last_err != 0)
                    last_err = AVERROR(last_err);
                if (last_err == 0) {
                    // Everything is ok, we seem to have a successful
                    // connection. Close other sockets and return this one.
                    for (j = 0; j < nb_attempts; j++)
                        if (j != i)
                            closesocket(attempts[j].fd);
                    *fd = attempts[i].fd;
                    getnameinfo(attempts[i].addr->ai_addr, attempts[i].addr->ai_addrlen,
                                hostbuf, sizeof(hostbuf), portbuf, sizeof(portbuf),
                                NI_NUMERICHOST | NI_NUMERICSERV);
                    av_log(h, AV_LOG_VERBOSE, "Successfully connected to %s port %s\n",
                                              hostbuf, portbuf);
                    return 0;
                }
            }
            if (attempts[i].deadline_us < av_gettime_relative() && !last_err)
                last_err = AVERROR(ETIMEDOUT);
            if (!last_err)
                continue;
            // Error (or timeout) for this socket; close the socket and remove
            // it from the attempts/pfd arrays, to let a new attempt start
            // directly.
            getnameinfo(attempts[i].addr->ai_addr, attempts[i].addr->ai_addrlen,
                        hostbuf, sizeof(hostbuf), portbuf, sizeof(portbuf),
                        NI_NUMERICHOST | NI_NUMERICSERV);
            av_strerror(last_err, errbuf, sizeof(errbuf));
            av_log(h, AV_LOG_VERBOSE, "Connection attempt to %s port %s "
                                      "failed: %s\n", hostbuf, portbuf, errbuf);
            closesocket(attempts[i].fd);
            memmove(&attempts[i], &attempts[i + 1],
                    (nb_attempts - i - 1) * sizeof(*attempts));
            memmove(&pfd[i], &pfd[i + 1],
                    (nb_attempts - i - 1) * sizeof(*pfd));
            i--;
            nb_attempts--;
        }
    }
    for (i = 0; i < nb_attempts; i++)
        closesocket(attempts[i].fd);
    if (last_err >= 0)
        last_err = AVERROR(ECONNREFUSED);
    if (last_err != AVERROR_EXIT) {
        av_strerror(last_err, errbuf, sizeof(errbuf));
        av_log(h, AV_LOG_ERROR, "Connection to %s failed: %s\n",
               h->filename, errbuf);
    }
    return last_err;
}