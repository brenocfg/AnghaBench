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
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct kevent {void* filter; TYPE_1__* udata; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  fflags; int /*<<< orphan*/  ident; int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {void* added; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ Socket ;

/* Variables and functions */
 void* EVFILT_READ ; 
 void* EVFILT_WRITE ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_DELETE ; 
 int /*<<< orphan*/  Infinity ; 
 int /*<<< orphan*/  NOTE_LOWAT ; 
 int kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  kq ; 

int
sockwant(Socket *s, int rw)
{
    int n = 0;
    struct kevent evs[2] = {{0}};
    struct kevent *ev = evs;
    struct timespec ts = {.tv_sec = 0, .tv_nsec = 0};

    if (s->added) {
        ev->ident = s->fd;
        ev->filter = s->added;
        ev->flags = EV_DELETE;
        ev++;
        n++;
    }

    if (rw) {
        ev->ident = s->fd;
        switch (rw) {
        case 'r':
            ev->filter = EVFILT_READ;
            break;
        case 'w':
            ev->filter = EVFILT_WRITE;
            break;
        default:
            // check only for hangup
            ev->filter = EVFILT_READ;
            ev->fflags = NOTE_LOWAT;
            ev->data = Infinity;
        }
        ev->flags = EV_ADD;
        ev->udata = s;
        s->added = ev->filter;
        ev++;
        n++;
    }

    return kevent(kq, evs, n, NULL, 0, &ts);
}