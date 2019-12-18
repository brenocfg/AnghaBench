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
 int /*<<< orphan*/  test_char () ; 
 int /*<<< orphan*/  test_compound () ; 
 int /*<<< orphan*/  test_float () ; 
 int /*<<< orphan*/  test_mbstring () ; 
 int /*<<< orphan*/  test_string () ; 
 int /*<<< orphan*/  test_ucn () ; 

void testmain() {
    print("literal");
    test_char();
    test_string();
    test_mbstring();
    test_float();
    test_ucn();
    test_compound();
}