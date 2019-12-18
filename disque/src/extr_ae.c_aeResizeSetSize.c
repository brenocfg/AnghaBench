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
typedef  int /*<<< orphan*/  aeFiredEvent ;
typedef  int /*<<< orphan*/  aeFileEvent ;
struct TYPE_5__ {int setsize; int maxfd; TYPE_2__* events; TYPE_2__* fired; } ;
typedef  TYPE_1__ aeEventLoop ;
struct TYPE_6__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int AE_ERR ; 
 int /*<<< orphan*/  AE_NONE ; 
 int AE_OK ; 
 int aeApiResize (TYPE_1__*,int) ; 
 void* zrealloc (TYPE_2__*,int) ; 

int aeResizeSetSize(aeEventLoop *eventLoop, int setsize) {
    int i;

    if (setsize == eventLoop->setsize) return AE_OK;
    if (eventLoop->maxfd >= setsize) return AE_ERR;
    if (aeApiResize(eventLoop,setsize) == -1) return AE_ERR;

    eventLoop->events = zrealloc(eventLoop->events,sizeof(aeFileEvent)*setsize);
    eventLoop->fired = zrealloc(eventLoop->fired,sizeof(aeFiredEvent)*setsize);
    eventLoop->setsize = setsize;

    /* Make sure that if we created new slots, they are initialized with
     * an AE_NONE mask. */
    for (i = eventLoop->maxfd+1; i < setsize; i++)
        eventLoop->events[i].mask = AE_NONE;
    return AE_OK;
}