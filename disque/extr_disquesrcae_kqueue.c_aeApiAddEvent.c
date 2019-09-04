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
struct kevent {int dummy; } ;
struct TYPE_4__ {TYPE_2__* apidata; } ;
typedef  TYPE_1__ aeEventLoop ;
struct TYPE_5__ {int /*<<< orphan*/  kqfd; } ;
typedef  TYPE_2__ aeApiState ;

/* Variables and functions */
 int AE_READABLE ; 
 int AE_WRITABLE ; 
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  EVFILT_WRITE ; 
 int /*<<< orphan*/  EV_ADD ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kevent (int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aeApiAddEvent(aeEventLoop *eventLoop, int fd, int mask) {
    aeApiState *state = eventLoop->apidata;
    struct kevent ke;

    if (mask & AE_READABLE) {
        EV_SET(&ke, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
        if (kevent(state->kqfd, &ke, 1, NULL, 0, NULL) == -1) return -1;
    }
    if (mask & AE_WRITABLE) {
        EV_SET(&ke, fd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
        if (kevent(state->kqfd, &ke, 1, NULL, 0, NULL) == -1) return -1;
    }
    return 0;
}