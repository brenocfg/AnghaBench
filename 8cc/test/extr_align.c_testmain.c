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
 int /*<<< orphan*/  test_alignas () ; 
 int /*<<< orphan*/  test_alignof () ; 
 int /*<<< orphan*/  test_constexpr () ; 

void testmain() {
    print("alignment");
    test_alignas();
    test_alignof();
    test_constexpr();
}