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
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  queue ;

/* Variables and functions */
 int /*<<< orphan*/ * createQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookupQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  needJobsForQueue (int /*<<< orphan*/ *,int) ; 

void needJobsForQueueName(robj *qname, int type) {
    queue *q = lookupQueue(qname);

    /* Create the queue if it does not exist. We need the queue structure
     * to store meta-data needed to broadcast NEEDJOBS messages anyway. */
    if (!q) q = createQueue(qname);
    needJobsForQueue(q,type);
}