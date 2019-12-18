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

__attribute__((used)) static void compare() {
    char *p = "abcdefg";
    expect(0, p == p + 1);
    expect(1, p == p);
    expect(0, p != p);
    expect(1, p != p + 1);
    expect(0, p < p);
    expect(1, p < p + 1);
    expect(0, p > p);
    expect(1, p + 1 > p);
    expect(1, p >= p);
    expect(1, p + 1 >= p);
    expect(0, p >= p + 1);
    expect(1, p <= p);
    expect(1, p <= p + 1);
    expect(0, p + 1 <= p);
    expect(4, sizeof(p == p + 1));
    expect(4, sizeof(p != p + 1));
    expect(4, sizeof(p < p + 1));
    expect(4, sizeof(p > p + 1));
    expect(4, sizeof(p <= p + 1));
    expect(4, sizeof(p >= p + 1));
}