#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* ptr; } ;
struct epoll_event {int events; TYPE_1__ data; } ;
struct TYPE_5__ {int added; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ Socket ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLPRI ; 
 int EPOLLRDHUP ; 
 int EPOLL_CTL_ADD ; 
 int EPOLL_CTL_DEL ; 
 int EPOLL_CTL_MOD ; 
 int /*<<< orphan*/  epfd ; 
 int epoll_ctl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct epoll_event*) ; 

int
sockwant(Socket *s, int rw)
{
    int op;

    if (!s->added && !rw) {
        return 0;
    } else if (!s->added && rw) {
        s->added = 1;
        op = EPOLL_CTL_ADD;
    } else if (!rw) {
        op = EPOLL_CTL_DEL;
    } else {
        op = EPOLL_CTL_MOD;
    }

    struct epoll_event ev = {.events=0};
    switch (rw) {
    case 'r':
        ev.events = EPOLLIN;
        break;
    case 'w':
        ev.events = EPOLLOUT;
        break;
    }
    ev.events |= EPOLLRDHUP | EPOLLPRI;
    ev.data.ptr = s;

    return epoll_ctl(epfd, op, s->fd, &ev);
}