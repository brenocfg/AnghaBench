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
struct cbq_sched_data {int /*<<< orphan*/  clhash; } ;
struct cbq_class {struct cbq_class* sibling; struct cbq_class* children; int /*<<< orphan*/  common; struct cbq_class* tparent; int /*<<< orphan*/  qdisc; } ;

/* Variables and functions */
 int /*<<< orphan*/  qdisc_class_hash_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cbq_sched_data* qdisc_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cbq_link_class(struct cbq_class *this)
{
	struct cbq_sched_data *q = qdisc_priv(this->qdisc);
	struct cbq_class *parent = this->tparent;

	this->sibling = this;
	qdisc_class_hash_insert(&q->clhash, &this->common);

	if (parent == NULL)
		return;

	if (parent->children == NULL) {
		parent->children = this;
	} else {
		this->sibling = parent->children->sibling;
		parent->children->sibling = this;
	}
}