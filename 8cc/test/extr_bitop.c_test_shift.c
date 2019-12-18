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

__attribute__((used)) static void test_shift() {
    expect(16, 1 << 4);
    expect(48, 3 << 4);

    expect(1, 15 >> 3);
    expect(2, 8 >> 2);

    expect(1, ((unsigned)-1) >> 31);
}