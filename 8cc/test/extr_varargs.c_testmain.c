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
 int /*<<< orphan*/  test_builtin () ; 
 int /*<<< orphan*/  test_float (double,double,double,double) ; 
 int /*<<< orphan*/  test_int (int,int,int,int,int) ; 
 int /*<<< orphan*/  test_mix (char*,double,int,char*,int) ; 
 int /*<<< orphan*/  test_va_list () ; 

void testmain() {
    print("varargs");
    test_builtin();
    test_int(1, 2, 3, 5, 8);
    test_float(1.0, 2.0, 4.0, 8.0);
    test_mix("abc", 2.0, 4, "d", 5);
    test_va_list();
}