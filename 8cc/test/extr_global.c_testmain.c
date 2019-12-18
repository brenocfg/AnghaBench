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
 int* a1 ; 
 int* a2 ; 
 int defaultint ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expect_string (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * intp ; 
 int /*<<< orphan*/  l1 ; 
 int* p1 ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  s1 ; 
 int /*<<< orphan*/  s2 ; 
 int val ; 
 int x1 ; 
 int x2 ; 
 int x3 ; 
 int x4 ; 
 int x5 ; 
 int x6 ; 

void testmain() {
    print("global variable");

    defaultint = 3;
    expect(3, defaultint);

    expect(21, val);
    val = 22;
    expect(22, val);
    expect(22, *p1);

    a1[1] = 23;
    expect(23, a1[1]);
    expect(25, a2[1]);

    x1 = 1;
    x2 = 2;
    expect(1, x1);
    expect(2, x2);
    x3 = 3;
    expect(3, x3);
    expect(4, x4);
    expect(5, x5);
    x6 = 6;
    expect(6, x6);

    expect_string("abcd", s1);
    expect_string("ABCD", s2);

    expectl(8, l1);
    expectl(9, *intp);
}