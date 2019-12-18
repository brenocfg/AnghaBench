#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_8__ {int portev_events; int portev_object; scalar_t__ portev_user; } ;
typedef  TYPE_2__ port_event_t ;
struct TYPE_9__ {TYPE_1__* fired; TYPE_4__* apidata; } ;
typedef  TYPE_3__ aeEventLoop ;
struct TYPE_10__ {int npending; int* pending_fds; uintptr_t* pending_masks; int /*<<< orphan*/  portfd; } ;
typedef  TYPE_4__ aeApiState ;
struct TYPE_7__ {int fd; int mask; } ;

/* Variables and functions */
 uintptr_t AE_NONE ; 
 int AE_READABLE ; 
 int AE_WRITABLE ; 
 scalar_t__ EINTR ; 
 scalar_t__ ETIME ; 
 int MAX_EVENT_BATCHSZ ; 
 int POLLIN ; 
 int POLLOUT ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ aeApiAssociate (char*,int /*<<< orphan*/ ,int,uintptr_t) ; 
 scalar_t__ errno ; 
 scalar_t__ evport_debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int port_getn (int /*<<< orphan*/ ,TYPE_2__*,int,int*,struct timespec*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp) {
    aeApiState *state = eventLoop->apidata;
    struct timespec timeout, *tsp;
    int mask, i;
    uint_t nevents;
    port_event_t event[MAX_EVENT_BATCHSZ];

    /*
     * If we've returned fd events before, we must re-associate them with the
     * port now, before calling port_get().  See the block comment at the top of
     * this file for an explanation of why.
     */
    for (i = 0; i < state->npending; i++) {
        if (state->pending_fds[i] == -1)
            /* This fd has since been deleted. */
            continue;

        if (aeApiAssociate("aeApiPoll", state->portfd,
            state->pending_fds[i], state->pending_masks[i]) != 0) {
            /* See aeApiDelEvent for why this case is fatal. */
            abort();
        }

        state->pending_masks[i] = AE_NONE;
        state->pending_fds[i] = -1;
    }

    state->npending = 0;

    if (tvp != NULL) {
        timeout.tv_sec = tvp->tv_sec;
        timeout.tv_nsec = tvp->tv_usec * 1000;
        tsp = &timeout;
    } else {
        tsp = NULL;
    }

    /*
     * port_getn can return with errno == ETIME having returned some events (!).
     * So if we get ETIME, we check nevents, too.
     */
    nevents = 1;
    if (port_getn(state->portfd, event, MAX_EVENT_BATCHSZ, &nevents,
        tsp) == -1 && (errno != ETIME || nevents == 0)) {
        if (errno == ETIME || errno == EINTR)
            return 0;

        /* Any other error indicates a bug. */
        perror("aeApiPoll: port_get");
        abort();
    }

    state->npending = nevents;

    for (i = 0; i < nevents; i++) {
            mask = 0;
            if (event[i].portev_events & POLLIN)
                mask |= AE_READABLE;
            if (event[i].portev_events & POLLOUT)
                mask |= AE_WRITABLE;

            eventLoop->fired[i].fd = event[i].portev_object;
            eventLoop->fired[i].mask = mask;

            if (evport_debug)
                fprintf(stderr, "aeApiPoll: fd %d mask 0x%x\n",
                    (int)event[i].portev_object, mask);

            state->pending_fds[i] = event[i].portev_object;
            state->pending_masks[i] = (uintptr_t)event[i].portev_user;
    }

    return nevents;
}