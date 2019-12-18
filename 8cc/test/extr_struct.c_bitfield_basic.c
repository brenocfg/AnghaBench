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

__attribute__((used)) static void bitfield_basic() {
    union {
        int i;
        struct { int a:5; int b:5; };
    } x;
    x.i = 0;
    x.a = 10;
    x.b = 11;
    expect(10, x.a);
    expect(11, x.b);
    expect(362, x.i); // 11 << 5 + 10 == 362
}