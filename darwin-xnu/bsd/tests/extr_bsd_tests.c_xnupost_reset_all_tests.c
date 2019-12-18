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
 int /*<<< orphan*/ * bsd_post_tests ; 
 int /*<<< orphan*/  bsd_post_tests_count ; 
 int /*<<< orphan*/ * kernel_post_tests ; 
 int /*<<< orphan*/  kernel_post_tests_count ; 
 int /*<<< orphan*/  xnupost_reset_tests (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
xnupost_reset_all_tests(void)
{
	xnupost_reset_tests(&bsd_post_tests[0], bsd_post_tests_count);
	xnupost_reset_tests(&kernel_post_tests[0], kernel_post_tests_count);
	return 0;
}