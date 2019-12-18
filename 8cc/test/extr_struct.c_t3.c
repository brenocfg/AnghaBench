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

__attribute__((used)) static void t3() {
    struct { int a; struct { char b; int c; } y; } x;
    x.a = 61;
    x.y.b = 3;
    x.y.c = 3;
    expect(67, x.a + x.y.b + x.y.c);
}