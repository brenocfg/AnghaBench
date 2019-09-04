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
struct TYPE_4__ {int fixed; int /*<<< orphan*/  p; int /*<<< orphan*/  memsize; scalar_t__ pos; scalar_t__ size; int /*<<< orphan*/ * ref; int /*<<< orphan*/ * lock; } ;
typedef  TYPE_1__ FIFO ;

/* Variables and functions */
 int /*<<< orphan*/  FIFO_INIT_MEM_SIZE ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_NEWFIFO_COUNT ; 
 int /*<<< orphan*/  Malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewLock () ; 
 int /*<<< orphan*/ * NewRef () ; 
 TYPE_1__* ZeroMalloc (int) ; 

FIFO *NewFifoEx2(bool fast, bool fixed)
{
	FIFO *f;

	// Memory allocation
	f = ZeroMalloc(sizeof(FIFO));

	if (fast == false)
	{
		f->lock = NewLock();
		f->ref = NewRef();
	}
	else
	{
		f->lock = NULL;
		f->ref = NULL;
	}

	f->size = f->pos = 0;
	f->memsize = FIFO_INIT_MEM_SIZE;
	f->p = Malloc(FIFO_INIT_MEM_SIZE);
	f->fixed = false;

	// KS
	KS_INC(KS_NEWFIFO_COUNT);

	return f;
}