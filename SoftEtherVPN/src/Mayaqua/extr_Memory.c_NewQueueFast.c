#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fifo; scalar_t__ num_item; int /*<<< orphan*/ * ref; int /*<<< orphan*/ * lock; } ;
typedef  TYPE_1__ QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_NEWQUEUE_COUNT ; 
 int /*<<< orphan*/  NewFifoFast () ; 
 TYPE_1__* ZeroMalloc (int) ; 

QUEUE *NewQueueFast()
{
	QUEUE *q;

	q = ZeroMalloc(sizeof(QUEUE));
	q->lock = NULL;
	q->ref = NULL;
	q->num_item = 0;
	q->fifo = NewFifoFast();

	// KS
	KS_INC(KS_NEWQUEUE_COUNT);

	return q;
}