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
typedef  int /*<<< orphan*/  u32 ;
struct Qdisc_class_ops {unsigned long (* get ) (struct Qdisc*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* put ) (struct Qdisc*,unsigned long) ;struct Qdisc* (* leaf ) (struct Qdisc*,unsigned long) ;} ;
struct Qdisc {TYPE_1__* ops; } ;
struct TYPE_2__ {struct Qdisc_class_ops* cl_ops; } ;

/* Variables and functions */
 unsigned long stub1 (struct Qdisc*,int /*<<< orphan*/ ) ; 
 struct Qdisc* stub2 (struct Qdisc*,unsigned long) ; 
 int /*<<< orphan*/  stub3 (struct Qdisc*,unsigned long) ; 

__attribute__((used)) static struct Qdisc *qdisc_leaf(struct Qdisc *p, u32 classid)
{
	unsigned long cl;
	struct Qdisc *leaf;
	const struct Qdisc_class_ops *cops = p->ops->cl_ops;

	if (cops == NULL)
		return NULL;
	cl = cops->get(p, classid);

	if (cl == 0)
		return NULL;
	leaf = cops->leaf(p, cl);
	cops->put(p, cl);
	return leaf;
}