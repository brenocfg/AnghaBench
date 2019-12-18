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
 scalar_t__ ktrace_owning_pid ; 
 scalar_t__ ktrace_owning_unique_id ; 

__attribute__((used)) static void
ktrace_release_ownership(void)
{
	ktrace_owning_unique_id = 0;
	ktrace_owning_pid = 0;
}