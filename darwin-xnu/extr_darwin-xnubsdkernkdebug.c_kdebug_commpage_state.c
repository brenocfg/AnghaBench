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
typedef  int uint32_t ;
struct TYPE_2__ {int kdebug_flags; } ;

/* Variables and functions */
 int KDBG_TYPEFILTER_CHECK ; 
 int KDEBUG_COMMPAGE_ENABLE_TRACE ; 
 int KDEBUG_COMMPAGE_ENABLE_TYPEFILTER ; 
 TYPE_1__ kd_ctrl_page ; 
 scalar_t__ kdebug_enable ; 

uint32_t
kdebug_commpage_state(void)
{
	if (kdebug_enable) {
		if (kd_ctrl_page.kdebug_flags & KDBG_TYPEFILTER_CHECK) {
			return KDEBUG_COMMPAGE_ENABLE_TYPEFILTER | KDEBUG_COMMPAGE_ENABLE_TRACE;
		}

		return KDEBUG_COMMPAGE_ENABLE_TRACE;
	}

	return 0;
}