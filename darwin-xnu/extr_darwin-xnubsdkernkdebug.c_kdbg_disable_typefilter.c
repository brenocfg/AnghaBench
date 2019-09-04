#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int kdebug_flags; int /*<<< orphan*/  kdebug_iops; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int KDBG_PIDCHECK ; 
 int KDBG_PIDEXCLUDE ; 
 int KDBG_TYPEFILTER_CHECK ; 
 int /*<<< orphan*/  KD_CALLBACK_TYPEFILTER_CHANGED ; 
 int /*<<< orphan*/  SLOW_CHECKS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  commpage_update_kdebug_state () ; 
 TYPE_1__ kd_ctrl_page ; 
 int /*<<< orphan*/  kdbg_iop_list_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdbg_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdbg_typefilter ; 
 int /*<<< orphan*/  typefilter_allow_all (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kdbg_disable_typefilter(void)
{
	bool notify_iops = kd_ctrl_page.kdebug_flags & KDBG_TYPEFILTER_CHECK;
	kd_ctrl_page.kdebug_flags &= ~KDBG_TYPEFILTER_CHECK;

	if ((kd_ctrl_page.kdebug_flags & (KDBG_PIDCHECK | KDBG_PIDEXCLUDE))) {
		kdbg_set_flags(SLOW_CHECKS, 0, TRUE);
	} else {
		kdbg_set_flags(SLOW_CHECKS, 0, FALSE);
	}
	commpage_update_kdebug_state();

	if (notify_iops) {
		/*
		 * Notify IOPs that the typefilter will now allow everything.
		 * Otherwise, they won't know a typefilter is no longer in
		 * effect.
		 */
		typefilter_allow_all(kdbg_typefilter);
		kdbg_iop_list_callback(kd_ctrl_page.kdebug_iops,
				KD_CALLBACK_TYPEFILTER_CHANGED, kdbg_typefilter);
	}
}