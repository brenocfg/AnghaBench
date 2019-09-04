#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  URLContext ;
typedef  int /*<<< orphan*/  SRTSOCKET ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  POLLING_TIME ; 
 int SRT_EPOLL_IN ; 
 int SRT_EPOLL_OUT ; 
 scalar_t__ SRT_ETIMEOUT ; 
 int libsrt_neterrno (int /*<<< orphan*/ *) ; 
 scalar_t__ srt_epoll_add_usock (int,int,int*) ; 
 scalar_t__ srt_epoll_remove_usock (int,int) ; 
 int srt_epoll_wait (int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ srt_getlasterror (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int libsrt_network_wait_fd(URLContext *h, int eid, int fd, int write)
{
    int ret, len = 1;
    int modes = write ? SRT_EPOLL_OUT : SRT_EPOLL_IN;
    SRTSOCKET ready[1];

    if (srt_epoll_add_usock(eid, fd, &modes) < 0)
        return libsrt_neterrno(h);
    if (write) {
        ret = srt_epoll_wait(eid, 0, 0, ready, &len, POLLING_TIME, 0, 0, 0, 0);
    } else {
        ret = srt_epoll_wait(eid, ready, &len, 0, 0, POLLING_TIME, 0, 0, 0, 0);
    }
    if (ret < 0) {
        if (srt_getlasterror(NULL) == SRT_ETIMEOUT)
            ret = AVERROR(EAGAIN);
        else
            ret = libsrt_neterrno(h);
    } else {
        ret = 0;
    }
    if (srt_epoll_remove_usock(eid, fd) < 0)
        return libsrt_neterrno(h);
    return ret;
}