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
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void t7() {
    int a;
    int *p1 = &a + 1;
    int *p2 = 1 + &a;
    expect(0, p1 - p2);
}