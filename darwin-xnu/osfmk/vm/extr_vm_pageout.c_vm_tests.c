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
 int /*<<< orphan*/  vm_test_collapse_compressor () ; 
 int /*<<< orphan*/  vm_test_device_pager_transpose () ; 
 int /*<<< orphan*/  vm_test_kernel_object_fault () ; 
 int /*<<< orphan*/  vm_test_page_wire_overflow_panic () ; 
 int /*<<< orphan*/  vm_test_wire_and_extract () ; 

void
vm_tests(void)
{
	vm_test_collapse_compressor();
	vm_test_wire_and_extract();
	vm_test_page_wire_overflow_panic();
	vm_test_kernel_object_fault();
	vm_test_device_pager_transpose();
}