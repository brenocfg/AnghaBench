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
struct user_desc {int read_exec_only; int seg_not_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct user_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void clear_user_desc(struct user_desc* info)
{
	/* Postcondition: LDT_empty(info) returns true. */
	memset(info, 0, sizeof(*info));

	/*
	 * Check the LDT_empty or the i386 sys_get_thread_area code - we obtain
	 * indeed an empty user_desc.
	 */
	info->read_exec_only = 1;
	info->seg_not_present = 1;
}