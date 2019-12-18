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
 int /*<<< orphan*/  test_computed_goto () ; 
 int /*<<< orphan*/  test_do () ; 
 int /*<<< orphan*/  test_for () ; 
 int /*<<< orphan*/  test_goto () ; 
 int /*<<< orphan*/  test_if () ; 
 int /*<<< orphan*/  test_label () ; 
 int /*<<< orphan*/  test_logor () ; 
 int /*<<< orphan*/  test_switch () ; 
 int /*<<< orphan*/  test_while () ; 

void testmain() {
    print("control flow");
    test_if();
    test_for();
    test_while();
    test_do();
    test_switch();
    test_goto();
    test_label();
    test_computed_goto();
    test_logor();
}