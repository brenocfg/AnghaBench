#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sym_entry {TYPE_1__* sym; int /*<<< orphan*/ * name; } ;
struct TYPE_2__ {scalar_t__ st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cmp_size(const void *lp, const void *rp)
{
	const struct sym_entry *l, *r;

	l = lp;
	r = rp;

	assert(l != NULL);
	assert(l->name != NULL);
	assert(l->sym != NULL);
	assert(r != NULL);
	assert(r->name != NULL);
	assert(r->sym != NULL);

	if (l->sym->st_size == r->sym->st_size)
		return (strcmp(l->name, r->name));

	return (l->sym->st_size - r->sym->st_size);
}