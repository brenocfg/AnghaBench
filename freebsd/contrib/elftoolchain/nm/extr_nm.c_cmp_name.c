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
struct sym_entry {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cmp_name(const void *l, const void *r)
{

	assert(l != NULL);
	assert(r != NULL);
	assert(((const struct sym_entry *)l)->name != NULL);
	assert(((const struct sym_entry *)r)->name != NULL);

	return (strcmp(((const struct sym_entry *)l)->name,
	    ((const struct sym_entry *)r)->name));
}