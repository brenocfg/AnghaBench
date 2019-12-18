#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* upl_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  ext_ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  upl_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  upl_unlock (TYPE_1__*) ; 

void
upl_set_referenced(
	upl_t		upl,
	boolean_t 	value)
{
	upl_lock(upl);
	if (value) {
		upl->ext_ref_count++;
	} else {
		if (!upl->ext_ref_count) {
			panic("upl_set_referenced not %p\n", upl);
		}
		upl->ext_ref_count--;
	}
	upl_unlock(upl);
}