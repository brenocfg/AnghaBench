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
typedef  int /*<<< orphan*/  queue_entry_t ;
struct TYPE_3__ {int /*<<< orphan*/  OSMT_refcnt; int /*<<< orphan*/  OSMT_state; int /*<<< orphan*/  OSMT_name; } ;
typedef  TYPE_1__* OSMallocTag ;

/* Variables and functions */
 int OSMT_RELEASED ; 
 int OSMT_VALID ; 
 int /*<<< orphan*/  OSMalloc_tag_spin_lock () ; 
 int /*<<< orphan*/  OSMalloc_tag_unlock () ; 
 scalar_t__ hw_atomic_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hw_compare_and_store (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void*,int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remque (int /*<<< orphan*/ ) ; 

void
OSMalloc_Tagfree(
	 OSMallocTag		tag)
{
	if (!hw_compare_and_store(OSMT_VALID, OSMT_VALID|OSMT_RELEASED, &tag->OSMT_state))
		panic("OSMalloc_Tagfree():'%s' has bad state 0x%08X \n", tag->OSMT_name, tag->OSMT_state);

	if (hw_atomic_sub(&tag->OSMT_refcnt, 1) == 0) {
		OSMalloc_tag_spin_lock();
		(void)remque((queue_entry_t)tag);
		OSMalloc_tag_unlock();
		kfree((void*)tag, sizeof(*tag));
	}
}