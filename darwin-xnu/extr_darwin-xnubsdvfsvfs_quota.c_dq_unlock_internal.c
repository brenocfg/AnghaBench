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
struct dquot {int dq_lflags; } ;

/* Variables and functions */
 int DQ_LLOCK ; 
 int DQ_LWANT ; 
 int /*<<< orphan*/  wakeup (int*) ; 

void
dq_unlock_internal(struct dquot *dq)
{
        int wanted = dq->dq_lflags & DQ_LWANT;

	dq->dq_lflags &= ~(DQ_LLOCK | DQ_LWANT);

	if (wanted)
	        wakeup(&dq->dq_lflags);
}