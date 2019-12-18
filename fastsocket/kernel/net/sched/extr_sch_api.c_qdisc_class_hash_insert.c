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
struct Qdisc_class_hash {int /*<<< orphan*/  hashelems; int /*<<< orphan*/ * hash; int /*<<< orphan*/  hashmask; } ;
struct Qdisc_class_common {int /*<<< orphan*/  hnode; int /*<<< orphan*/  classid; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int qdisc_class_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qdisc_class_hash_insert(struct Qdisc_class_hash *clhash,
			     struct Qdisc_class_common *cl)
{
	unsigned int h;

	INIT_HLIST_NODE(&cl->hnode);
	h = qdisc_class_hash(cl->classid, clhash->hashmask);
	hlist_add_head(&cl->hnode, &clhash->hash[h]);
	clhash->hashelems++;
}