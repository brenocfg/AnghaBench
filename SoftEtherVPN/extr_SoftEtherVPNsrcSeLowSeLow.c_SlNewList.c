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
struct TYPE_3__ {int num_reserved; void** p; scalar_t__ num_item; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ SL_LIST ;

/* Variables and functions */
 int SL_INIT_NUM_RESERVED ; 
 int /*<<< orphan*/  SlNewLock () ; 
 scalar_t__ SlZeroMalloc (int) ; 

SL_LIST *SlNewList()
{
	SL_LIST *o;

	o = (SL_LIST *)SlZeroMalloc(sizeof(SL_LIST));

	o->lock = SlNewLock();

	o->num_item = 0;
	o->num_reserved = SL_INIT_NUM_RESERVED;

	o->p = (void **)SlZeroMalloc(sizeof(void *) * o->num_reserved);

	return o;
}