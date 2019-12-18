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
 int /*<<< orphan*/  ktest_current_time ; 
 int /*<<< orphan*/  ktest_emit_testend () ; 
 int /*<<< orphan*/  ktest_test_index ; 
 int /*<<< orphan*/  mach_absolute_time () ; 

void
ktest_testend() {
	ktest_current_time = mach_absolute_time();
	ktest_emit_testend();
	ktest_test_index++;
}