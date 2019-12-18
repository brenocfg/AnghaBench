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
typedef  int /*<<< orphan*/  my_policy_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  MY_POLICY_FIXEDPRI ; 
 int /*<<< orphan*/  MY_POLICY_REALTIME ; 
 int /*<<< orphan*/  MY_POLICY_TIMESHARE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

my_policy_type_t
parse_thread_policy(const char *str)
{
	if (strcmp(str, "timeshare") == 0) {
		return MY_POLICY_TIMESHARE;
	} else if (strcmp(str, "realtime") == 0) {
		return MY_POLICY_REALTIME;
	} else if (strcmp(str, "fixed") == 0) {
		return MY_POLICY_FIXEDPRI;
	} else {
		printf("Invalid thread policy %s\n", str);
		exit(1);
	}
}