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
struct TYPE_3__ {int /*<<< orphan*/  num_item; int /*<<< orphan*/  fifo; } ;
typedef  TYPE_1__ QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_INSERT_QUEUE_COUNT ; 
 int /*<<< orphan*/  WriteFifo (int /*<<< orphan*/ ,void**,int) ; 

void InsertQueue(QUEUE *q, void *p)
{
	// Validate arguments
	if (q == NULL || p == NULL)
	{
		return;
	}

	// Write to the FIFO
	WriteFifo(q->fifo, &p, sizeof(void *));

	q->num_item++;

	/*{
		static UINT max_num_item;
		static UINT64 next_tick = 0;
		UINT64 now = Tick64();

		max_num_item = MAX(q->num_item, max_num_item);

		if (next_tick == 0 || next_tick <= now)
		{
			next_tick = now + (UINT64)1000;

			printf("max_queue = %u\n", max_num_item);
		}
	}*/

	// KS
	KS_INC(KS_INSERT_QUEUE_COUNT);
}