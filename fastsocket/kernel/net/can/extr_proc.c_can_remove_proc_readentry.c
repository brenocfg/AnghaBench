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
 scalar_t__ can_dir ; 
 int /*<<< orphan*/  remove_proc_entry (char const*,scalar_t__) ; 

__attribute__((used)) static void can_remove_proc_readentry(const char *name)
{
	if (can_dir)
		remove_proc_entry(name, can_dir);
}