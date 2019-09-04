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
typedef  int /*<<< orphan*/  tre_literal_t ;
struct literals {int len; int cap; int /*<<< orphan*/  mem; int /*<<< orphan*/ ** a; } ;

/* Variables and functions */
 int /*<<< orphan*/ * tre_mem_calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** xrealloc (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static tre_literal_t *tre_new_lit(struct literals *p)
{
	tre_literal_t **a;
	if (p->len >= p->cap) {
		if (p->cap >= 1<<15)
			return 0;
		p->cap *= 2;
		a = xrealloc(p->a, p->cap * sizeof *p->a);
		if (!a)
			return 0;
		p->a = a;
	}
	a = p->a + p->len++;
	*a = tre_mem_calloc(p->mem, sizeof **a);
	return *a;
}