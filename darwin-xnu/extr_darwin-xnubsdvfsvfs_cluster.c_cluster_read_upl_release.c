#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  upl_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int UPL_ABORT_FREE_ON_EMPTY ; 
 int UPL_ABORT_REFERENCE ; 
 int /*<<< orphan*/  ubc_upl_abort_range (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
cluster_read_upl_release(upl_t upl, int start_pg, int last_pg, int take_reference)
{
	int range;
	int abort_flags = UPL_ABORT_FREE_ON_EMPTY;

	if ((range = last_pg - start_pg)) {
		if (take_reference)
			abort_flags |= UPL_ABORT_REFERENCE;

		ubc_upl_abort_range(upl, start_pg * PAGE_SIZE, range * PAGE_SIZE, abort_flags);
	}
}