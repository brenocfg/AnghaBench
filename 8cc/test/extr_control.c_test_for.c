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

__attribute__((used)) static void test_for() {
    int i;
    int acc = 0;
    for (i = 0; i < 5; i++) {
        acc = acc + i;
    }
    expect(10, acc);

    acc = 0;
    for (i = 0; i < 5; i++) {
        acc = acc + i;
    }
    expect(10, acc);

    acc = 0;
    for (i = 0; i < 100; i++) {
        if (i < 5) continue;
        if (i == 9) break;
        acc += i;
    }
    expect(5 + 6 + 7 + 8, acc);

    for (int x = 3, y = 5, z = 8; x < 100; x++, y++, z+=2)
        expect(z, x + y);

    for (;;)
        break;
    for (i = 0; i < 100; i++)
        ;

    i = 0;
    for (; 0.5;) {
        i = 68;
        break;
    }
    expect(68, i);
}