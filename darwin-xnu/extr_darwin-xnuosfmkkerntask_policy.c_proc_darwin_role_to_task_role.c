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
typedef  int integer_t ;

/* Variables and functions */
 int EINVAL ; 
#define  PRIO_DARWIN_ROLE_DARWIN_BG 134 
#define  PRIO_DARWIN_ROLE_DEFAULT 133 
#define  PRIO_DARWIN_ROLE_NON_UI 132 
#define  PRIO_DARWIN_ROLE_TAL_LAUNCH 131 
#define  PRIO_DARWIN_ROLE_UI 130 
#define  PRIO_DARWIN_ROLE_UI_FOCAL 129 
#define  PRIO_DARWIN_ROLE_UI_NON_FOCAL 128 
 int TASK_BACKGROUND_APPLICATION ; 
 int TASK_DARWINBG_APPLICATION ; 
 int TASK_DEFAULT_APPLICATION ; 
 int TASK_FOREGROUND_APPLICATION ; 
 int TASK_NONUI_APPLICATION ; 
 int TASK_THROTTLE_APPLICATION ; 
 int TASK_UNSPECIFIED ; 

int
proc_darwin_role_to_task_role(int darwin_role, int* task_role)
{
	integer_t role = TASK_UNSPECIFIED;

	switch (darwin_role) {
		case PRIO_DARWIN_ROLE_DEFAULT:
			role = TASK_UNSPECIFIED;
			break;
		case PRIO_DARWIN_ROLE_UI_FOCAL:
			role = TASK_FOREGROUND_APPLICATION;
			break;
		case PRIO_DARWIN_ROLE_UI:
			role = TASK_DEFAULT_APPLICATION;
			break;
		case PRIO_DARWIN_ROLE_NON_UI:
			role = TASK_NONUI_APPLICATION;
			break;
		case PRIO_DARWIN_ROLE_UI_NON_FOCAL:
			role = TASK_BACKGROUND_APPLICATION;
			break;
		case PRIO_DARWIN_ROLE_TAL_LAUNCH:
			role = TASK_THROTTLE_APPLICATION;
			break;
		case PRIO_DARWIN_ROLE_DARWIN_BG:
			role = TASK_DARWINBG_APPLICATION;
			break;
		default:
			return EINVAL;
	}

	*task_role = role;

	return 0;
}