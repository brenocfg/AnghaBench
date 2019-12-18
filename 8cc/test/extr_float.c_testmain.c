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
 int /*<<< orphan*/  expect (double,double) ; 
 int /*<<< orphan*/  expectd (double,double) ; 
 int /*<<< orphan*/  expectf (double,double) ; 
 int /*<<< orphan*/  print (char*) ; 
 double recursive (int) ; 
 int /*<<< orphan*/  std () ; 
 double tf1 (int) ; 
 double tf2 (int) ; 
 double tf3 (int) ; 

void testmain() {
    print("float");
    std();

    expect(0.7, .7);
    float v1 = 10.0;
    float v2 = v1;
    expectf(10.0, v1);
    expectf(10.0, v2);
    return;
    double v3 = 20.0;
    double v4 = v3;
    expectd(20.0, v3);
    expectd(20.0, v4);

    expectf(1.0, 1.0);
    expectf(1.5, 1.0 + 0.5);
    expectf(0.5, 1.0 - 0.5);
    expectf(2.0, 1.0 * 2.0);
    expectf(0.25, 1.0 / 4.0);

    expectf(3.0, 1.0 + 2);
    expectf(2.5, 5 - 2.5);
    expectf(2.0, 1.0 * 2);
    expectf(0.25, 1.0 / 4);

    expectf(10.5, tf1(10.5));
    expectf(10.0, tf1(10));
    expectf(10.6, tf2(10.6));
    expectf(10.0, tf2(10));
    expectf(10.0, tf3(10.7));
    expectf(10.0, tf3(10));

    expectd(1.0, tf1(1.0));
    expectd(10.0, tf1(10));
    expectd(2.0, tf2(2.0));
    expectd(10.0, tf2(10));
    expectd(11.0, tf3(11.5));
    expectd(10.0, tf3(10));

    expectd(3.33, recursive(100));
}