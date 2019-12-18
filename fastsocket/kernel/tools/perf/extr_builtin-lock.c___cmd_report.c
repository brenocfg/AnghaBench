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
 int /*<<< orphan*/  print_result () ; 
 scalar_t__ read_events () ; 
 scalar_t__ select_key () ; 
 int /*<<< orphan*/  setup_pager () ; 
 int /*<<< orphan*/  sort_result () ; 

__attribute__((used)) static int __cmd_report(void)
{
	setup_pager();

	if ((select_key() != 0) ||
	    (read_events() != 0))
		return -1;

	sort_result();
	print_result();

	return 0;
}