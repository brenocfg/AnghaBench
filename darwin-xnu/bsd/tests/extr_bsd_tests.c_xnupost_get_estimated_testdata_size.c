#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int kcs_elem_offset; } ;

/* Variables and functions */
 int bsd_post_tests_count ; 
 TYPE_1__* kc_xnupost_test_def ; 
 int kc_xnupost_test_def_count ; 
 int kcs_get_elem_size (TYPE_1__*) ; 
 int kernel_post_tests_count ; 

uint32_t
xnupost_get_estimated_testdata_size(void)
{
	uint32_t total_tests = bsd_post_tests_count + kernel_post_tests_count;
	uint32_t elem_size = kc_xnupost_test_def[kc_xnupost_test_def_count - 1].kcs_elem_offset +
	                     kcs_get_elem_size(&kc_xnupost_test_def[kc_xnupost_test_def_count - 1]);
	uint32_t retval = 1024; /* account for type definition and mach timebase */
	retval += 1024;         /* kernel version and boot-args string data */
	retval += (total_tests * elem_size);

	return retval;
}