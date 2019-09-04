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
struct TYPE_3__ {int OSMT_state; int /*<<< orphan*/  OSMT_refcnt; int /*<<< orphan*/  OSMT_name; } ;
typedef  TYPE_1__* OSMallocTag ;

/* Variables and functions */
 int OSMT_VALID ; 
 int OSMT_VALID_MASK ; 
 int /*<<< orphan*/  hw_atomic_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int) ; 

void
OSMalloc_Tagref(
	 OSMallocTag		tag)
{
	if (!((tag->OSMT_state & OSMT_VALID_MASK) == OSMT_VALID)) 
		panic("OSMalloc_Tagref():'%s' has bad state 0x%08X\n", tag->OSMT_name, tag->OSMT_state);

	(void)hw_atomic_add(&tag->OSMT_refcnt, 1);
}