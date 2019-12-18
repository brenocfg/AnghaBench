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
 int /*<<< orphan*/  arrow () ; 
 int /*<<< orphan*/  assign () ; 
 int /*<<< orphan*/  bitfield_basic () ; 
 int /*<<< orphan*/  bitfield_initializer () ; 
 int /*<<< orphan*/  bitfield_mix () ; 
 int /*<<< orphan*/  bitfield_union () ; 
 int /*<<< orphan*/  bitfield_unnamed () ; 
 int /*<<< orphan*/  empty_struct () ; 
 int /*<<< orphan*/  flexible_member () ; 
 int /*<<< orphan*/  incomplete () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  t1 () ; 
 int /*<<< orphan*/  t10 () ; 
 int /*<<< orphan*/  t11 () ; 
 int /*<<< orphan*/  t12 () ; 
 int /*<<< orphan*/  t13 () ; 
 int /*<<< orphan*/  t14 () ; 
 int /*<<< orphan*/  t2 () ; 
 int /*<<< orphan*/  t3 () ; 
 int /*<<< orphan*/  t4 () ; 
 int /*<<< orphan*/  t5 () ; 
 int /*<<< orphan*/  t6 () ; 
 int /*<<< orphan*/  t7 () ; 
 int /*<<< orphan*/  t8 () ; 
 int /*<<< orphan*/  t9 () ; 
 int /*<<< orphan*/  test_offsetof () ; 
 int /*<<< orphan*/  unnamed () ; 

void testmain() {
    print("struct");
    t1();
    t2();
    t3();
    t4();
    t5();
    t6();
    t7();
    t8();
    t9();
    t10();
    t11();
    t12();
    t13();
    t14();
    unnamed();
    assign();
    arrow();
    incomplete();
    bitfield_basic();
    bitfield_mix();
    bitfield_union();
    bitfield_unnamed();
    bitfield_initializer();
    test_offsetof();
    flexible_member();
    empty_struct();
}