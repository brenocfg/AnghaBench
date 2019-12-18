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
struct TYPE_3__ {scalar_t__ num_item; int /*<<< orphan*/  fifo; } ;
typedef  TYPE_1__ QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  KS_GETNEXT_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadFifo (int /*<<< orphan*/ ,void**,int) ; 

void *GetNext(QUEUE *q)
{
	void *p = NULL;
	// Validate arguments
	if (q == NULL)
	{
		return NULL;
	}

	if (q->num_item == 0)
	{
		// No items
		return NULL;
	}

	// Read from the FIFO
	ReadFifo(q->fifo, &p, sizeof(void *));
	q->num_item--;

	// KS
	KS_INC(KS_GETNEXT_COUNT);

	return p;
}