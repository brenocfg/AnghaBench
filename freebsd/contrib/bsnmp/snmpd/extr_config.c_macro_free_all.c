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
struct macro {struct macro* value; struct macro* name; int /*<<< orphan*/  perm; } ;

/* Variables and functions */
 struct macro* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct macro* LIST_NEXT (struct macro*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct macro*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct macro*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  macros ; 

__attribute__((used)) static void
macro_free_all(void)
{
	static struct macro *m, *m1;

	m = LIST_FIRST(&macros);
	while (m != NULL) {
		m1 = LIST_NEXT(m, link);
		if (!m->perm) {
			free(m->name);
			free(m->value);
			LIST_REMOVE(m, link);
			free(m);
		}
		m = m1;
	}
}