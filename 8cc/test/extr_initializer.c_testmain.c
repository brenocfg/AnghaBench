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
 int /*<<< orphan*/  test_array () ; 
 int /*<<< orphan*/  test_array_designator () ; 
 int /*<<< orphan*/  test_complex_designator () ; 
 int /*<<< orphan*/  test_excessive () ; 
 int /*<<< orphan*/  test_nested () ; 
 int /*<<< orphan*/  test_primitive () ; 
 int /*<<< orphan*/  test_string () ; 
 int /*<<< orphan*/  test_struct () ; 
 int /*<<< orphan*/  test_struct_designator () ; 
 int /*<<< orphan*/  test_typedef () ; 
 int /*<<< orphan*/  test_zero () ; 

void testmain() {
    print("initializer");

    test_array();
    test_string();
    test_struct();
    test_primitive();
    test_nested();
    test_array_designator();
    test_struct_designator();
    test_complex_designator();
    test_zero();
    test_typedef();
    test_excessive();
}