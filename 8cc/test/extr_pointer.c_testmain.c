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
 int /*<<< orphan*/  compare () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  subtract () ; 
 int /*<<< orphan*/  t1 () ; 
 int /*<<< orphan*/  t2 () ; 
 int /*<<< orphan*/  t3 () ; 
 int /*<<< orphan*/  t4 () ; 
 int /*<<< orphan*/  t5 () ; 
 int /*<<< orphan*/  t6 () ; 
 int /*<<< orphan*/  t7 () ; 

void testmain() {
    print("pointer");
    t1();
    t2();
    t3();
    t4();
    t5();
    t6();
    t7();
    subtract();
    compare();
}