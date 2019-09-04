#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * clients; } ;
typedef  TYPE_1__ queue ;
struct TYPE_5__ {int /*<<< orphan*/  ready_queues; } ;

/* Variables and functions */
 scalar_t__ DICT_OK ; 
 scalar_t__ dictAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  incrRefCount (int /*<<< orphan*/ ) ; 
 scalar_t__ listLength (int /*<<< orphan*/ *) ; 
 TYPE_3__ server ; 

void signalQueueAsReady(queue *q) {
    if (q->clients == NULL || listLength(q->clients) == 0) return;
    if (dictAdd(server.ready_queues,q->name,NULL) == DICT_OK)
        incrRefCount(q->name);
}