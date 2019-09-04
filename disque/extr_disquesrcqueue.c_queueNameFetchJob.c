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
typedef  int /*<<< orphan*/  job ;

/* Variables and functions */
 int /*<<< orphan*/ * lookupQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * queueFetchJob (int /*<<< orphan*/ *,unsigned long*) ; 

job *queueNameFetchJob(robj *qname, unsigned long *qlen) {
    queue *q = lookupQueue(qname);
    return q ? queueFetchJob(q,qlen) : NULL;
}