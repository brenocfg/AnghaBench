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
 int /*<<< orphan*/  test_align () ; 
 int /*<<< orphan*/  test_pointer () ; 
 int /*<<< orphan*/  test_signed () ; 
 int /*<<< orphan*/  test_storage_class () ; 
 int /*<<< orphan*/  test_type () ; 
 int /*<<< orphan*/  test_typedef () ; 
 int /*<<< orphan*/  test_unsigned () ; 
 int /*<<< orphan*/  test_unusual_order () ; 

void testmain() {
    print("type system");
    test_type();
    test_signed();
    test_unsigned();
    test_storage_class();
    test_pointer();
    test_unusual_order();
    test_typedef();
    test_align();
}