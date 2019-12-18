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
struct TYPE_3__ {int num_reserved; int sorted; int /*<<< orphan*/ * cmp; void* p; scalar_t__ Param1; scalar_t__ num_item; int /*<<< orphan*/ * ref; int /*<<< orphan*/ * lock; } ;
typedef  TYPE_1__ LIST ;
typedef  int /*<<< orphan*/  COMPARE ;

/* Variables and functions */
 int INIT_NUM_RESERVED ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_NEWLIST_COUNT ; 
 void* Malloc (int) ; 
 void* MallocFast (int) ; 
 int /*<<< orphan*/ * NewLock () ; 
 int /*<<< orphan*/ * NewRef () ; 

LIST *NewListEx2(COMPARE *cmp, bool fast, bool fast_malloc)
{
	LIST *o;

	if (fast_malloc == false)
	{
		o = Malloc(sizeof(LIST));
	}
	else
	{
		o = MallocFast(sizeof(LIST));
	}

	if (fast == false)
	{
		o->lock = NewLock();
		o->ref = NewRef();
	}
	else
	{
		o->lock = NULL;
		o->ref = NULL;
	}
	o->num_item = 0;
	o->num_reserved = INIT_NUM_RESERVED;
	o->Param1 = 0;

	if (fast_malloc == false)
	{
		o->p = Malloc(sizeof(void *) * o->num_reserved);
	}
	else
	{
		o->p = MallocFast(sizeof(void *) * o->num_reserved);
	}

	o->cmp = cmp;
	o->sorted = true;

	// KS
	KS_INC(KS_NEWLIST_COUNT);

	return o;
}