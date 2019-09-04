#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ Ns; } ;
typedef  TYPE_1__ L2TP_QUEUE ;

/* Variables and functions */
 scalar_t__ L2TP_SEQ_LT (scalar_t__,scalar_t__) ; 

int CmpL2TPQueueForRecv(void *p1, void *p2)
{
	L2TP_QUEUE *q1, *q2;
	// Validate arguments
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	q1 = *(L2TP_QUEUE **)p1;
	q2 = *(L2TP_QUEUE **)p2;
	if (q1 == NULL || q2 == NULL)
	{
		return 0;
	}

	if (L2TP_SEQ_LT(q1->Ns, q2->Ns))
	{
		return -1;
	}
	else if (q1->Ns == q2->Ns)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}