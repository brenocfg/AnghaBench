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
typedef  scalar_t__ u32 ;
struct context {scalar_t__ len; } ;
struct sidtab_node {scalar_t__ sid; struct context context; struct sidtab_node* next; } ;
struct sidtab {struct sidtab_node** htable; } ;

/* Variables and functions */
 scalar_t__ SECINITSID_UNLABELED ; 
 int SIDTAB_HASH (scalar_t__) ; 

__attribute__((used)) static struct context *sidtab_search_core(struct sidtab *s, u32 sid, int force)
{
	int hvalue;
	struct sidtab_node *cur;

	if (!s)
		return NULL;

	hvalue = SIDTAB_HASH(sid);
	cur = s->htable[hvalue];
	while (cur && sid > cur->sid)
		cur = cur->next;

	if (force && cur && sid == cur->sid && cur->context.len)
		return &cur->context;

	if (cur == NULL || sid != cur->sid || cur->context.len) {
		/* Remap invalid SIDs to the unlabeled SID. */
		sid = SECINITSID_UNLABELED;
		hvalue = SIDTAB_HASH(sid);
		cur = s->htable[hvalue];
		while (cur && sid > cur->sid)
			cur = cur->next;
		if (!cur || sid != cur->sid)
			return NULL;
	}

	return &cur->context;
}