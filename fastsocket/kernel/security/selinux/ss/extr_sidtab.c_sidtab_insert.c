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
struct sidtab_node {scalar_t__ sid; struct sidtab_node* next; int /*<<< orphan*/  context; } ;
struct sidtab {scalar_t__ next_sid; int /*<<< orphan*/  nel; struct sidtab_node** htable; } ;
struct context {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int SIDTAB_HASH (scalar_t__) ; 
 scalar_t__ context_cpy (int /*<<< orphan*/ *,struct context*) ; 
 int /*<<< orphan*/  kfree (struct sidtab_node*) ; 
 struct sidtab_node* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

int sidtab_insert(struct sidtab *s, u32 sid, struct context *context)
{
	int hvalue, rc = 0;
	struct sidtab_node *prev, *cur, *newnode;

	if (!s) {
		rc = -ENOMEM;
		goto out;
	}

	hvalue = SIDTAB_HASH(sid);
	prev = NULL;
	cur = s->htable[hvalue];
	while (cur && sid > cur->sid) {
		prev = cur;
		cur = cur->next;
	}

	if (cur && sid == cur->sid) {
		rc = -EEXIST;
		goto out;
	}

	newnode = kmalloc(sizeof(*newnode), GFP_ATOMIC);
	if (newnode == NULL) {
		rc = -ENOMEM;
		goto out;
	}
	newnode->sid = sid;
	if (context_cpy(&newnode->context, context)) {
		kfree(newnode);
		rc = -ENOMEM;
		goto out;
	}

	if (prev) {
		newnode->next = prev->next;
		wmb();
		prev->next = newnode;
	} else {
		newnode->next = s->htable[hvalue];
		wmb();
		s->htable[hvalue] = newnode;
	}

	s->nel++;
	if (sid >= s->next_sid)
		s->next_sid = sid + 1;
out:
	return rc;
}