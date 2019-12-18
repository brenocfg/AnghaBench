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
typedef  scalar_t__ u_int16_t ;
struct pf_tags {int dummy; } ;
struct pf_tagname {scalar_t__ tag; scalar_t__ ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 struct pf_tagname* TAILQ_FIRST (struct pf_tags*) ; 
 struct pf_tagname* TAILQ_NEXT (struct pf_tagname*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct pf_tags*,struct pf_tagname*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FREE (struct pf_tagname*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 

__attribute__((used)) static void
tag_unref(struct pf_tags *head, u_int16_t tag)
{
	struct pf_tagname	*p, *next;

	if (tag == 0)
		return;

	for (p = TAILQ_FIRST(head); p != NULL; p = next) {
		next = TAILQ_NEXT(p, entries);
		if (tag == p->tag) {
			if (--p->ref == 0) {
				TAILQ_REMOVE(head, p, entries);
				_FREE(p, M_TEMP);
			}
			break;
		}
	}
}