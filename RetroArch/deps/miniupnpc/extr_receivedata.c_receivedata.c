#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr_in6 {int sin6_scope_id; } ;
struct sockaddr {int dummy; } ;
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  src_addr ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_3__ {int tv_sec; int tv_usec; } ;
typedef  TYPE_1__ TIMEVAL ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POLLIN ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

int
receivedata(int socket,
            char * data, int length,
            int timeout, unsigned int * scope_id)
{
#ifdef MINIUPNPC_GET_SRC_ADDR
	struct sockaddr_storage src_addr;
	socklen_t src_addr_len = sizeof(src_addr);
#endif	/* MINIUPNPC_GET_SRC_ADDR */
    int n;
#if !defined(_WIN32) && !defined(__amigaos__) && !defined(__amigaos4__)
	/* using poll */
    struct pollfd fds[1]; /* for the poll */
#ifdef MINIUPNPC_IGNORE_EINTR
    do {
#endif	/* MINIUPNPC_IGNORE_EINTR */
        fds[0].fd = socket;
        fds[0].events = POLLIN;
        n = poll(fds, 1, timeout);
#ifdef MINIUPNPC_IGNORE_EINTR
    } while(n < 0 && errno == EINTR);
#endif	/* MINIUPNPC_IGNORE_EINTR */
    if(n < 0)
        return -1;
    /* timeout */
    if(n == 0)
        return 0;
#else	/* !defined(_WIN32) && !defined(__amigaos__) && !defined(__amigaos4__) */
	/* using select under _WIN32 and amigaos */
    fd_set socketSet;
    TIMEVAL timeval;
    FD_ZERO(&socketSet);
    FD_SET(socket, &socketSet);
    timeval.tv_sec = timeout / 1000;
    timeval.tv_usec = (timeout % 1000) * 1000;
    n = select(FD_SETSIZE, &socketSet, NULL, NULL, &timeval);
    if(n < 0)
       return -1;
    if(n == 0)
       return 0;
#endif	/* !defined(_WIN32) && !defined(__amigaos__) && !defined(__amigaos4__) */
#ifdef MINIUPNPC_GET_SRC_ADDR
	memset(&src_addr, 0, sizeof(src_addr));
	n = recvfrom(socket, data, length, 0,
	             (struct sockaddr *)&src_addr, &src_addr_len);
#else	/* MINIUPNPC_GET_SRC_ADDR */
	n = (int)recv(socket, data, length, 0);
#endif	/* MINIUPNPC_GET_SRC_ADDR */
#ifdef MINIUPNPC_GET_SRC_ADDR
	if (src_addr.ss_family == AF_INET6) {
		const struct sockaddr_in6 * src_addr6 = (struct sockaddr_in6 *)&src_addr;
#ifdef DEBUG
		printf("scope_id=%u\n", src_addr6->sin6_scope_id);
#endif	/* DEBUG */
		if(scope_id)
			*scope_id = src_addr6->sin6_scope_id;
	}
#endif	/* MINIUPNPC_GET_SRC_ADDR */
	return n;
}