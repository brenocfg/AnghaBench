#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* upl_t ;
struct TYPE_9__ {scalar_t__ ref_count; scalar_t__ upl_iodone; } ;

/* Variables and functions */
 int /*<<< orphan*/  upl_callout_iodone (TYPE_1__*) ; 
 int /*<<< orphan*/  upl_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  upl_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  upl_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vector_upl_deallocate (TYPE_1__*) ; 
 scalar_t__ vector_upl_is_valid (TYPE_1__*) ; 

void
upl_deallocate(upl_t upl)
{
	upl_lock(upl);

	if (--upl->ref_count == 0) {
		if(vector_upl_is_valid(upl))
			vector_upl_deallocate(upl);
		upl_unlock(upl);

		if (upl->upl_iodone)
		        upl_callout_iodone(upl);

		upl_destroy(upl);
	} else
		upl_unlock(upl);
}