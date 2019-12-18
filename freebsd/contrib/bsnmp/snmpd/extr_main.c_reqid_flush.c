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
struct lmodule {int dummy; } ;
struct idrange {struct lmodule* owner; } ;

/* Variables and functions */
 struct idrange* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct idrange* TAILQ_NEXT (struct idrange*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct idrange*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct idrange*) ; 
 int /*<<< orphan*/  idrange_list ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
reqid_flush(struct lmodule *mod)
{
	struct idrange *p, *p1;

	p = TAILQ_FIRST(&idrange_list);
	while (p != NULL) {
		p1 = TAILQ_NEXT(p, link);
		if (p->owner == mod) {
			TAILQ_REMOVE(&idrange_list, p, link);
			free(p);
		}
		p = p1;
	}
}