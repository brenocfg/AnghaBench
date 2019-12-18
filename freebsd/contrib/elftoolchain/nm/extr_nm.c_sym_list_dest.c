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
struct sym_head {int dummy; } ;
struct sym_entry {struct sym_entry* name; struct sym_entry* sym; } ;

/* Variables and functions */
 struct sym_entry* STAILQ_FIRST (struct sym_head*) ; 
 struct sym_entry* STAILQ_NEXT (struct sym_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sym_entry*) ; 
 int /*<<< orphan*/  sym_entries ; 

__attribute__((used)) static void
sym_list_dest(struct sym_head *headp)
{
	struct sym_entry *ep, *ep_n;

	if (headp == NULL)
		return;

	ep = STAILQ_FIRST(headp);
	while (ep != NULL) {
		ep_n = STAILQ_NEXT(ep, sym_entries);
		free(ep->sym);
		free(ep->name);
		free(ep);
		ep = ep_n;
	}
}