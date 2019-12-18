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
struct list_head {int /*<<< orphan*/  prev; int /*<<< orphan*/  next; } ;

/* Variables and functions */

__attribute__((used)) static inline void fixup(unsigned long s, unsigned long e, int d,
			 struct list_head *l)
{
	unsigned long *pp;

	pp = (unsigned long *)&l->next;
	if (*pp >= s && *pp < e)
		*pp += d;

	pp = (unsigned long *)&l->prev;
	if (*pp >= s && *pp < e)
		*pp += d;
}