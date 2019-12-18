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
 int /*<<< orphan*/  print (char*) ; 

void testmain() {
    print("comparison operators");
    expect(1, 1 < 2);
    expect(0, 2 < 1);
    expect(1, 1 == 1);
    expect(0, 1 == 2);
    expect(0, 1 != 1);
    expect(1, 1 != 2);

    expect(1, 1 <= 2);
    expect(1, 2 <= 2);
    expect(0, 2 <= 1);

    expect(0, 1 >= 2);
    expect(1, 2 >= 2);
    expect(1, 2 >= 1);

    int i = -1;
    expect(0, i >= 0);

    expect(1, 10.0 == 10.0);
    expect(0, 10.0 == 20.0);
    expect(0, 10.0 != 10.0);
    expect(1, 10.0 != 20.0);

    expect(1, 10.0f == 10.0f);
    expect(0, 10.0f == 20.0f);
    expect(0, 10.0f != 10.0f);
    expect(1, 10.0f != 20.0f);

    expect(1, 10.0f == 10.0);
    expect(0, 10.0f == 20.0);
    expect(0, 10.0f != 10.0);
    expect(1, 10.0f != 20.0);
}