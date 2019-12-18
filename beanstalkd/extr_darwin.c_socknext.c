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
struct timespec {int tv_sec; int tv_nsec; } ;
struct kevent {int flags; int filter; int /*<<< orphan*/ * udata; } ;
typedef  int int64 ;
typedef  int /*<<< orphan*/  Socket ;

/* Variables and functions */
 scalar_t__ EINTR ; 
#define  EVFILT_READ 129 
#define  EVFILT_WRITE 128 
 int EV_EOF ; 
 scalar_t__ errno ; 
 int kevent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kevent*,int,struct timespec*) ; 
 int /*<<< orphan*/  kq ; 
 int /*<<< orphan*/  twarn (char*) ; 

int
socknext(Socket **s, int64 timeout)
{
    int r;
    struct kevent ev;
    static struct timespec ts;

    ts.tv_sec = timeout / 1000000000;
    ts.tv_nsec = timeout % 1000000000;
    r = kevent(kq, NULL, 0, &ev, 1, &ts);
    if (r == -1 && errno != EINTR) {
        twarn("kevent");
        return -1;
    }

    if (r > 0) {
        *s = ev.udata;
        if (ev.flags & EV_EOF) {
            return 'h';
        }
        switch (ev.filter) {
        case EVFILT_READ:
            return 'r';
        case EVFILT_WRITE:
            return 'w';
        }
    }
    return 0;
}