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
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expectd (double,double) ; 
 int /*<<< orphan*/  expectf (double,float) ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  test_signedcast () ; 
 int /*<<< orphan*/  test_unsignedcast () ; 

void testmain() {
    print("cast");
    expectf(1, (int)1);
    expectf(1.0, (float)1);
    expectd(2.0, (double)2);

    int a[3];
    *(int *)(a + 2) = 5;
    expect(5, a[2]);

    test_signedcast();
    test_unsignedcast();
}