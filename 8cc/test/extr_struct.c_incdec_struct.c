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

__attribute__((used)) static void incdec_struct() {
    struct incdec {
	int x, y;
    } a[] = { { 1, 2 }, { 3, 4 } }, *p = a;
    expect(1, p->x);
    expect(2, p->y);
    p++;
    expect(3, p->x);
    expect(4, p->y);
    p--;
    expect(1, p->x);
    expect(2, p->y);
    ++p;
    expect(3, p->x);
    expect(4, p->y);
    --p;
    expect(1, p->x);
    expect(2, p->y);
}