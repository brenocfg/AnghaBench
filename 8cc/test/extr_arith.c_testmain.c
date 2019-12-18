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
 int /*<<< orphan*/  test_basic () ; 
 int /*<<< orphan*/  test_bool () ; 
 int /*<<< orphan*/  test_comma () ; 
 int /*<<< orphan*/  test_inc_dec () ; 
 int /*<<< orphan*/  test_relative () ; 
 int /*<<< orphan*/  test_ternary () ; 
 int /*<<< orphan*/  test_unary () ; 

void testmain() {
    print("basic arithmetic");
    test_basic();
    test_relative();
    test_inc_dec();
    test_bool();
    test_unary();
    test_ternary();
    test_comma();
}