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
typedef  int u32 ;
struct tcf_proto {int dummy; } ;
struct tcf_exts {int dummy; } ;
struct route4_head {struct route4_bucket** table; } ;
struct TYPE_2__ {void* classid; } ;
struct route4_filter {int handle; int id; int iif; int /*<<< orphan*/  exts; TYPE_1__ res; struct route4_bucket* bkt; struct route4_filter* next; } ;
struct route4_bucket {struct route4_filter** ht; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t TCA_ROUTE4_CLASSID ; 
 size_t TCA_ROUTE4_FROM ; 
 size_t TCA_ROUTE4_IIF ; 
 size_t TCA_ROUTE4_TO ; 
 unsigned int from_hash (int) ; 
 struct route4_bucket* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  route_ext_map ; 
 int /*<<< orphan*/  tcf_bind_filter (struct tcf_proto*,TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  tcf_exts_change (struct tcf_proto*,int /*<<< orphan*/ *,struct tcf_exts*) ; 
 int /*<<< orphan*/  tcf_exts_destroy (struct tcf_proto*,struct tcf_exts*) ; 
 int tcf_exts_validate (struct tcf_proto*,struct nlattr**,struct nlattr*,struct tcf_exts*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_tree_lock (struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_tree_unlock (struct tcf_proto*) ; 
 unsigned int to_hash (int) ; 

__attribute__((used)) static int route4_set_parms(struct tcf_proto *tp, unsigned long base,
	struct route4_filter *f, u32 handle, struct route4_head *head,
	struct nlattr **tb, struct nlattr *est, int new)
{
	int err;
	u32 id = 0, to = 0, nhandle = 0x8000;
	struct route4_filter *fp;
	unsigned int h1;
	struct route4_bucket *b;
	struct tcf_exts e;

	err = tcf_exts_validate(tp, tb, est, &e, &route_ext_map);
	if (err < 0)
		return err;

	err = -EINVAL;
	if (tb[TCA_ROUTE4_TO]) {
		if (new && handle & 0x8000)
			goto errout;
		to = nla_get_u32(tb[TCA_ROUTE4_TO]);
		if (to > 0xFF)
			goto errout;
		nhandle = to;
	}

	if (tb[TCA_ROUTE4_FROM]) {
		if (tb[TCA_ROUTE4_IIF])
			goto errout;
		id = nla_get_u32(tb[TCA_ROUTE4_FROM]);
		if (id > 0xFF)
			goto errout;
		nhandle |= id << 16;
	} else if (tb[TCA_ROUTE4_IIF]) {
		id = nla_get_u32(tb[TCA_ROUTE4_IIF]);
		if (id > 0x7FFF)
			goto errout;
		nhandle |= (id | 0x8000) << 16;
	} else
		nhandle |= 0xFFFF << 16;

	if (handle && new) {
		nhandle |= handle & 0x7F00;
		if (nhandle != handle)
			goto errout;
	}

	h1 = to_hash(nhandle);
	if ((b = head->table[h1]) == NULL) {
		err = -ENOBUFS;
		b = kzalloc(sizeof(struct route4_bucket), GFP_KERNEL);
		if (b == NULL)
			goto errout;

		tcf_tree_lock(tp);
		head->table[h1] = b;
		tcf_tree_unlock(tp);
	} else {
		unsigned int h2 = from_hash(nhandle >> 16);
		err = -EEXIST;
		for (fp = b->ht[h2]; fp; fp = fp->next)
			if (fp->handle == f->handle)
				goto errout;
	}

	tcf_tree_lock(tp);
	if (tb[TCA_ROUTE4_TO])
		f->id = to;

	if (tb[TCA_ROUTE4_FROM])
		f->id = to | id<<16;
	else if (tb[TCA_ROUTE4_IIF])
		f->iif = id;

	f->handle = nhandle;
	f->bkt = b;
	tcf_tree_unlock(tp);

	if (tb[TCA_ROUTE4_CLASSID]) {
		f->res.classid = nla_get_u32(tb[TCA_ROUTE4_CLASSID]);
		tcf_bind_filter(tp, &f->res, base);
	}

	tcf_exts_change(tp, &f->exts, &e);

	return 0;
errout:
	tcf_exts_destroy(tp, &e);
	return err;
}