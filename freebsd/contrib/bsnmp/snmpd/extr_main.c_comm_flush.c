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
struct community {struct community* string; struct lmodule* owner; } ;

/* Variables and functions */
 struct community* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct community* TAILQ_NEXT (struct community*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct community*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  community_list ; 
 int /*<<< orphan*/  free (struct community*) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
comm_flush(struct lmodule *mod)
{
	struct community *p, *p1;

	p = TAILQ_FIRST(&community_list);
	while (p != NULL) {
		p1 = TAILQ_NEXT(p, link);
		if (p->owner == mod) {
			free(p->string);
			TAILQ_REMOVE(&community_list, p, link);
			free(p);
		}
		p = p1;
	}
}