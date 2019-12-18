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
struct baz {int a; int b; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

f1(struct baz *p) {
	p->a = p->b = 0;
	if (p->b)
		printf("p->b != 0!\n");
	p->a = 0x3; p->b = 0xf;
	printf("p->a = 0x%x, p->b = 0x%x\n", p->a, p->b);
}