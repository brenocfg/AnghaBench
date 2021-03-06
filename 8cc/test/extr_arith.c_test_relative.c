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

__attribute__((used)) static void test_relative() {
    expect(1, 1 > 0);
    expect(1, 0 < 1);
    expect(0, 1 < 0);
    expect(0, 0 > 1);
    expect(0, 1 > 1);
    expect(0, 1 < 1);
    expect(1, 1 >= 0);
    expect(1, 0 <= 1);
    expect(0, 1 <= 0);
    expect(0, 0 >= 1);
    expect(1, 1 >= 1);
    expect(1, 1 <= 1);
    expect(1, 0xFFFFFFFFU > 1);
    expect(1, 1 < 0xFFFFFFFFU);
    expect(1, 0xFFFFFFFFU >= 1);
    expect(1, 1 <= 0xFFFFFFFFU);
    expect(1, -1 > 1U);
    expect(1, -1 >= 1U);
    expect(0, -1L > 1U);
    expect(0, -1L >= 1U);
    expect(0, 1.0 < 0.0);
    expect(1, 0.0 < 1.0);
}