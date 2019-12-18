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

__attribute__((used)) static void t4() {
    struct tag4 { int a; struct { char b; int c; } y; } x;
    struct tag4 s;
    s.a = 61;
    s.y.b = 3;
    s.y.c = 3;
    expect(67, s.a + s.y.b + s.y.c);
}