#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * ptr; } ;
struct epoll_event {int events; TYPE_1__ data; } ;
typedef  int int64 ;
typedef  int /*<<< orphan*/  Socket ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDHUP ; 
 int /*<<< orphan*/  epfd ; 
 int epoll_wait (int /*<<< orphan*/ ,struct epoll_event*,int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  twarn (char*) ; 

int
socknext(Socket **s, int64 timeout)
{
    int r;
    struct epoll_event ev = {.events=0};

    r = epoll_wait(epfd, &ev, 1, (int)(timeout/1000000));
    if (r == -1 && errno != EINTR) {
        twarn("epoll_wait");
        exit(1);
    }

    if (r > 0) {
        *s = ev.data.ptr;
        if (ev.events & (EPOLLHUP|EPOLLRDHUP)) {
            return 'h';
        } else if (ev.events & EPOLLIN) {
            return 'r';
        } else if (ev.events & EPOLLOUT) {
            return 'w';
        }
    }
    return 0;
}