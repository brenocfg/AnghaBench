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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  kdebug_slowcheck; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ kd_ctrl_page ; 
 int /*<<< orphan*/  kdebug_debugid_explicitly_enabled (int /*<<< orphan*/ ) ; 

boolean_t
kdebug_debugid_enabled(uint32_t debugid)
{
	/* if no filtering is enabled */
	if (!kd_ctrl_page.kdebug_slowcheck) {
		return TRUE;
	}

	return kdebug_debugid_explicitly_enabled(debugid);
}