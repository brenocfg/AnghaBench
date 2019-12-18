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
struct baz {int a; int /*<<< orphan*/  b; } ;

/* Variables and functions */
 int /*<<< orphan*/  f1 (struct baz*) ; 
 scalar_t__ i ; 

f2(struct baz *p) {
	p->a = (i==0);
	p->b = (f1(p),0);
}