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
typedef  TYPE_1__* upl_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPL_CLEAR_DIRTY ; 

void
upl_clear_dirty(
	upl_t		upl,
	boolean_t 	value)
{
	if (value) {
		upl->flags |= UPL_CLEAR_DIRTY;
	} else {
		upl->flags &= ~UPL_CLEAR_DIRTY;
	}
}