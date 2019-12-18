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
 int /*<<< orphan*/  expect (int,char) ; 

__attribute__((used)) static void unnamed() {
    struct {
        union {
            struct { int x; int y; };
            struct { char c[8]; };
        };
    } v;
    v.x = 1;
    v.y = 7;
    expect(1, v.c[0]);
    expect(7, v.c[4]);
}