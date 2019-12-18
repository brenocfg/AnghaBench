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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
typedef  int u16 ;
struct nlattr {int dummy; } ;
struct dsmark_qdisc_data {int indices; int /*<<< orphan*/ * q; int /*<<< orphan*/  set_tc_index; void* default_index; int /*<<< orphan*/ * value; int /*<<< orphan*/ * mask; } ;
struct Qdisc {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* NO_DEFAULT_INDEX ; 
 size_t TCA_DSMARK_DEFAULT_INDEX ; 
 size_t TCA_DSMARK_INDICES ; 
 int /*<<< orphan*/  TCA_DSMARK_MAX ; 
 size_t TCA_DSMARK_SET_TC_INDEX ; 
 int /*<<< orphan*/  dsmark_policy ; 
 int hweight32 (int) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nla_get_flag (struct nlattr*) ; 
 void* nla_get_u16 (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 int /*<<< orphan*/  pr_debug (char*,struct Qdisc*,...) ; 
 int /*<<< orphan*/ * qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct dsmark_qdisc_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int dsmark_init(struct Qdisc *sch, struct nlattr *opt)
{
	struct dsmark_qdisc_data *p = qdisc_priv(sch);
	struct nlattr *tb[TCA_DSMARK_MAX + 1];
	int err = -EINVAL;
	u32 default_index = NO_DEFAULT_INDEX;
	u16 indices;
	u8 *mask;

	pr_debug("dsmark_init(sch %p,[qdisc %p],opt %p)\n", sch, p, opt);

	if (!opt)
		goto errout;

	err = nla_parse_nested(tb, TCA_DSMARK_MAX, opt, dsmark_policy);
	if (err < 0)
		goto errout;

	err = -EINVAL;
	indices = nla_get_u16(tb[TCA_DSMARK_INDICES]);

	if (hweight32(indices) != 1)
		goto errout;

	if (tb[TCA_DSMARK_DEFAULT_INDEX])
		default_index = nla_get_u16(tb[TCA_DSMARK_DEFAULT_INDEX]);

	mask = kmalloc(indices * 2, GFP_KERNEL);
	if (mask == NULL) {
		err = -ENOMEM;
		goto errout;
	}

	p->mask = mask;
	memset(p->mask, 0xff, indices);

	p->value = p->mask + indices;
	memset(p->value, 0, indices);

	p->indices = indices;
	p->default_index = default_index;
	p->set_tc_index = nla_get_flag(tb[TCA_DSMARK_SET_TC_INDEX]);

	p->q = qdisc_create_dflt(qdisc_dev(sch), sch->dev_queue,
				 &pfifo_qdisc_ops, sch->handle);
	if (p->q == NULL)
		p->q = &noop_qdisc;

	pr_debug("dsmark_init: qdisc %p\n", p->q);

	err = 0;
errout:
	return err;
}