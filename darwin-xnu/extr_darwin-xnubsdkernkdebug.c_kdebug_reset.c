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

/* Variables and functions */
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  kdbg_clear () ; 
 int /*<<< orphan*/  kdbg_lock_init () ; 
 scalar_t__ kdbg_typefilter ; 
 int /*<<< orphan*/  ktrace_assert_lock_held () ; 
 int /*<<< orphan*/  typefilter_allow_class (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typefilter_reject_all (scalar_t__) ; 

void
kdebug_reset(void)
{
	ktrace_assert_lock_held();

	kdbg_lock_init();

	kdbg_clear();
	if (kdbg_typefilter) {
		typefilter_reject_all(kdbg_typefilter);
		typefilter_allow_class(kdbg_typefilter, DBG_TRACE);
	}
}