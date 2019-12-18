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
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
#define  UU_PROFILE_DEFAULT 129 
#define  UU_PROFILE_LAUNCHER 128 
 int uu_exit_fatal_value ; 
 int /*<<< orphan*/  uu_exit_ok_value ; 
 int uu_exit_usage_value ; 

void
uu_alt_exit(int profile)
{
	switch (profile) {
	case UU_PROFILE_DEFAULT:
		uu_exit_ok_value = EXIT_SUCCESS;
		uu_exit_fatal_value = EXIT_FAILURE;
		uu_exit_usage_value = 2;
		break;
	case UU_PROFILE_LAUNCHER:
		uu_exit_ok_value = EXIT_SUCCESS;
		uu_exit_fatal_value = 124;
		uu_exit_usage_value = 125;
		break;
	}
}