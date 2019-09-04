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
 int /*<<< orphan*/  bsd_post_tests ; 
 int /*<<< orphan*/  bsd_post_tests_count ; 
 int xnupost_run_tests (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bsd_do_post()
{
	return xnupost_run_tests(bsd_post_tests, bsd_post_tests_count);
}