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
 int PRIO_DARWIN_ROLE_DARWIN_BG ; 
 int PRIO_DARWIN_ROLE_DEFAULT ; 
 int PRIO_DARWIN_ROLE_NON_UI ; 
 int PRIO_DARWIN_ROLE_TAL_LAUNCH ; 
 int PRIO_DARWIN_ROLE_UI ; 
 int PRIO_DARWIN_ROLE_UI_FOCAL ; 
 int PRIO_DARWIN_ROLE_UI_NON_FOCAL ; 
#define  TASK_BACKGROUND_APPLICATION 134 
#define  TASK_DARWINBG_APPLICATION 133 
#define  TASK_DEFAULT_APPLICATION 132 
#define  TASK_FOREGROUND_APPLICATION 131 
#define  TASK_NONUI_APPLICATION 130 
#define  TASK_THROTTLE_APPLICATION 129 
#define  TASK_UNSPECIFIED 128 

int
proc_task_role_to_darwin_role(int task_role)
{
	switch (task_role) {
		case TASK_FOREGROUND_APPLICATION:
			return PRIO_DARWIN_ROLE_UI_FOCAL;
		case TASK_BACKGROUND_APPLICATION:
			return PRIO_DARWIN_ROLE_UI_NON_FOCAL;
		case TASK_NONUI_APPLICATION:
			return PRIO_DARWIN_ROLE_NON_UI;
		case TASK_DEFAULT_APPLICATION:
			return PRIO_DARWIN_ROLE_UI;
		case TASK_THROTTLE_APPLICATION:
			return PRIO_DARWIN_ROLE_TAL_LAUNCH;
		case TASK_DARWINBG_APPLICATION:
			return PRIO_DARWIN_ROLE_DARWIN_BG;
		case TASK_UNSPECIFIED:
		default:
			return PRIO_DARWIN_ROLE_DEFAULT;
	}
}