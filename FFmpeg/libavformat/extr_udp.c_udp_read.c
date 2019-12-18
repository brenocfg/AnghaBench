#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_5__ {int flags; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {int circular_buffer_error; int /*<<< orphan*/  filters; int /*<<< orphan*/  udp_fd; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; scalar_t__ fifo; } ;
typedef  TYPE_2__ UDPContext ;

/* Variables and functions */
 int AVERROR (scalar_t__) ; 
 int AVIO_FLAG_NONBLOCK ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_RL32 (int /*<<< orphan*/ *) ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  av_fifo_drain (scalar_t__,int) ; 
 int /*<<< orphan*/  av_fifo_generic_read (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int av_fifo_size (scalar_t__) ; 
 int av_gettime () ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ ff_ip_check_source_lists (struct sockaddr_storage*,int /*<<< orphan*/ *) ; 
 int ff_neterrno () ; 
 int ff_network_wait_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int recvfrom (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 

__attribute__((used)) static int udp_read(URLContext *h, uint8_t *buf, int size)
{
    UDPContext *s = h->priv_data;
    int ret;
    struct sockaddr_storage addr;
    socklen_t addr_len = sizeof(addr);
#if HAVE_PTHREAD_CANCEL
    int avail, nonblock = h->flags & AVIO_FLAG_NONBLOCK;

    if (s->fifo) {
        pthread_mutex_lock(&s->mutex);
        do {
            avail = av_fifo_size(s->fifo);
            if (avail) { // >=size) {
                uint8_t tmp[4];

                av_fifo_generic_read(s->fifo, tmp, 4, NULL);
                avail= AV_RL32(tmp);
                if(avail > size){
                    av_log(h, AV_LOG_WARNING, "Part of datagram lost due to insufficient buffer size\n");
                    avail= size;
                }

                av_fifo_generic_read(s->fifo, buf, avail, NULL);
                av_fifo_drain(s->fifo, AV_RL32(tmp) - avail);
                pthread_mutex_unlock(&s->mutex);
                return avail;
            } else if(s->circular_buffer_error){
                int err = s->circular_buffer_error;
                pthread_mutex_unlock(&s->mutex);
                return err;
            } else if(nonblock) {
                pthread_mutex_unlock(&s->mutex);
                return AVERROR(EAGAIN);
            }
            else {
                /* FIXME: using the monotonic clock would be better,
                   but it does not exist on all supported platforms. */
                int64_t t = av_gettime() + 100000;
                struct timespec tv = { .tv_sec  =  t / 1000000,
                                       .tv_nsec = (t % 1000000) * 1000 };
                if (pthread_cond_timedwait(&s->cond, &s->mutex, &tv) < 0) {
                    pthread_mutex_unlock(&s->mutex);
                    return AVERROR(errno == ETIMEDOUT ? EAGAIN : errno);
                }
                nonblock = 1;
            }
        } while( 1);
    }
#endif

    if (!(h->flags & AVIO_FLAG_NONBLOCK)) {
        ret = ff_network_wait_fd(s->udp_fd, 0);
        if (ret < 0)
            return ret;
    }
    ret = recvfrom(s->udp_fd, buf, size, 0, (struct sockaddr *)&addr, &addr_len);
    if (ret < 0)
        return ff_neterrno();
    if (ff_ip_check_source_lists(&addr, &s->filters))
        return AVERROR(EINTR);
    return ret;
}