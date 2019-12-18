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
 int /*<<< orphan*/  expect (int,unsigned int) ; 

__attribute__((used)) static void test_basic() {
    expect(0, 0);
    expect(3, 1 + 2);
    expect(3, 1 + 2);
    expect(10, 1 + 2 + 3 + 4);
    expect(11, 1 + 2 * 3 + 4);
    expect(14, 1 * 2 + 3 * 4);
    expect(4, 4 / 2 + 6 / 3);
    expect(4, 24 / 2 / 3);
    expect(3, 24 % 7);
    expect(0, 24 % 3);
    expect(98, 'a' + 1);
    int a = 0 - 1;
    expect(0 - 1, a);
    expect(-1, a);
    expect(0, a + 1);
    expect(1, +1);
    expect(1, (unsigned)4000000001 % 2);
}