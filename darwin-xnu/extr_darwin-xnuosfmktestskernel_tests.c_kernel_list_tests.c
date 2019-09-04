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
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  kernel_post_tests ; 
 int /*<<< orphan*/  kernel_post_tests_count ; 
 int /*<<< orphan*/  xnupost_list_tests (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
kernel_list_tests()
{
	return xnupost_list_tests(kernel_post_tests, kernel_post_tests_count);
}