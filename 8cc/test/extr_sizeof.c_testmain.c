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
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  test_arrays () ; 
 int /*<<< orphan*/  test_constexpr () ; 
 int /*<<< orphan*/  test_literals () ; 
 int /*<<< orphan*/  test_pointers () ; 
 int /*<<< orphan*/  test_primitives () ; 
 int /*<<< orphan*/  test_struct () ; 
 int /*<<< orphan*/  test_unsigned () ; 
 int /*<<< orphan*/  test_vars () ; 

void testmain() {
    print("sizeof");
    test_primitives();
    test_pointers();
    test_unsigned();
    test_literals();
    test_arrays();
    test_vars();
    test_struct();
    test_constexpr();
}