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
 int /*<<< orphan*/  i31_impl ; 
 int /*<<< orphan*/  i32_impl ; 
 int /*<<< orphan*/ * impl ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_modint () ; 

int
main(void)
{
	printf("===== i32 ======\n");
	impl = &i32_impl;
	test_modint();
	printf("===== i31 ======\n");
	impl = &i31_impl;
	test_modint();
	/*
	test_RSA_core();
	*/
	return 0;
}