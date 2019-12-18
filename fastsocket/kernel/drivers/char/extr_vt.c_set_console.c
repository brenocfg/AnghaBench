#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ mode; } ;
struct vc_data {scalar_t__ vc_mode; TYPE_1__ vt_mode; } ;
struct TYPE_4__ {struct vc_data* d; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ KD_GRAPHICS ; 
 scalar_t__ VT_AUTO ; 
 size_t fg_console ; 
 int /*<<< orphan*/  schedule_console_callback () ; 
 TYPE_2__* vc_cons ; 
 int /*<<< orphan*/  vc_cons_allocated (int) ; 
 scalar_t__ vt_dont_switch ; 
 int want_console ; 

int set_console(int nr)
{
	struct vc_data *vc = vc_cons[fg_console].d;

	if (!vc_cons_allocated(nr) || vt_dont_switch ||
		(vc->vt_mode.mode == VT_AUTO && vc->vc_mode == KD_GRAPHICS)) {

		/*
		 * Console switch will fail in console_callback() or
		 * change_console() so there is no point scheduling
		 * the callback
		 *
		 * Existing set_console() users don't check the return
		 * value so this shouldn't break anything
		 */
		return -EINVAL;
	}

	want_console = nr;
	schedule_console_callback();

	return 0;
}