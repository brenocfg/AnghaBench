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
 int /*<<< orphan*/  test_count ; 
 char const* test_name ; 
 int /*<<< orphan*/  test_status ; 
 int /*<<< orphan*/  test_status_pass ; 

void
p_test_init(const char *name)
{

	test_count++;
	test_status = test_status_pass;
	test_name = name;
}