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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ source_type; scalar_t__ target_type; scalar_t__ target_class; int specified; } ;
struct avtab_node {TYPE_1__ key; struct avtab_node* next; } ;
struct avtab_key {int specified; scalar_t__ source_type; scalar_t__ target_type; scalar_t__ target_class; } ;
struct avtab_datum {int dummy; } ;
struct avtab {struct avtab_node** htable; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int AVTAB_ENABLED ; 
 int AVTAB_ENABLED_OLD ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int avtab_hash (struct avtab_key*,int /*<<< orphan*/ ) ; 
 struct avtab_node* avtab_insert_node (struct avtab*,int,struct avtab_node*,struct avtab_node*,struct avtab_key*,struct avtab_datum*) ; 

__attribute__((used)) static int avtab_insert(struct avtab *h, struct avtab_key *key, struct avtab_datum *datum)
{
	int hvalue;
	struct avtab_node *prev, *cur, *newnode;
	u16 specified = key->specified & ~(AVTAB_ENABLED|AVTAB_ENABLED_OLD);

	if (!h || !h->htable)
		return -EINVAL;

	hvalue = avtab_hash(key, h->mask);
	for (prev = NULL, cur = h->htable[hvalue];
	     cur;
	     prev = cur, cur = cur->next) {
		if (key->source_type == cur->key.source_type &&
		    key->target_type == cur->key.target_type &&
		    key->target_class == cur->key.target_class &&
		    (specified & cur->key.specified))
			return -EEXIST;
		if (key->source_type < cur->key.source_type)
			break;
		if (key->source_type == cur->key.source_type &&
		    key->target_type < cur->key.target_type)
			break;
		if (key->source_type == cur->key.source_type &&
		    key->target_type == cur->key.target_type &&
		    key->target_class < cur->key.target_class)
			break;
	}

	newnode = avtab_insert_node(h, hvalue, prev, cur, key, datum);
	if (!newnode)
		return -ENOMEM;

	return 0;
}