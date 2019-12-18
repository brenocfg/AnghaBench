#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct tcmsg {int tcm_handle; } ;
struct tcf_proto {int dummy; } ;
struct TYPE_6__ {int nkeys; scalar_t__ mask; scalar_t__ val; } ;
struct TYPE_4__ {int classid; } ;
struct tc_u_knode {int handle; int /*<<< orphan*/  exts; TYPE_3__* pf; TYPE_3__ sel; int /*<<< orphan*/  indev; TYPE_3__ mark; TYPE_2__* ht_down; TYPE_1__ res; scalar_t__ ht_up; } ;
struct tc_u_hnode {int divisor; } ;
struct tc_u32_pcnt {int dummy; } ;
struct tc_u32_key {int dummy; } ;
struct sk_buff {int len; } ;
struct nlattr {int dummy; } ;
struct TYPE_5__ {int handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  NLA_PUT_STRING (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  TCA_U32_CLASSID ; 
 int /*<<< orphan*/  TCA_U32_DIVISOR ; 
 int /*<<< orphan*/  TCA_U32_HASH ; 
 int /*<<< orphan*/  TCA_U32_INDEV ; 
 int /*<<< orphan*/  TCA_U32_LINK ; 
 int /*<<< orphan*/  TCA_U32_MARK ; 
 int /*<<< orphan*/  TCA_U32_PCNT ; 
 int /*<<< orphan*/  TCA_U32_SEL ; 
 scalar_t__ TC_U32_KEY (int) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ tcf_exts_dump (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tcf_exts_dump_stats (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u32_ext_map ; 

__attribute__((used)) static int u32_dump(struct tcf_proto *tp, unsigned long fh,
		     struct sk_buff *skb, struct tcmsg *t)
{
	struct tc_u_knode *n = (struct tc_u_knode*)fh;
	struct nlattr *nest;

	if (n == NULL)
		return skb->len;

	t->tcm_handle = n->handle;

	nest = nla_nest_start(skb, TCA_OPTIONS);
	if (nest == NULL)
		goto nla_put_failure;

	if (TC_U32_KEY(n->handle) == 0) {
		struct tc_u_hnode *ht = (struct tc_u_hnode*)fh;
		u32 divisor = ht->divisor+1;
		NLA_PUT_U32(skb, TCA_U32_DIVISOR, divisor);
	} else {
		NLA_PUT(skb, TCA_U32_SEL,
			sizeof(n->sel) + n->sel.nkeys*sizeof(struct tc_u32_key),
			&n->sel);
		if (n->ht_up) {
			u32 htid = n->handle & 0xFFFFF000;
			NLA_PUT_U32(skb, TCA_U32_HASH, htid);
		}
		if (n->res.classid)
			NLA_PUT_U32(skb, TCA_U32_CLASSID, n->res.classid);
		if (n->ht_down)
			NLA_PUT_U32(skb, TCA_U32_LINK, n->ht_down->handle);

#ifdef CONFIG_CLS_U32_MARK
		if (n->mark.val || n->mark.mask)
			NLA_PUT(skb, TCA_U32_MARK, sizeof(n->mark), &n->mark);
#endif

		if (tcf_exts_dump(skb, &n->exts, &u32_ext_map) < 0)
			goto nla_put_failure;

#ifdef CONFIG_NET_CLS_IND
		if(strlen(n->indev))
			NLA_PUT_STRING(skb, TCA_U32_INDEV, n->indev);
#endif
#ifdef CONFIG_CLS_U32_PERF
		NLA_PUT(skb, TCA_U32_PCNT,
		sizeof(struct tc_u32_pcnt) + n->sel.nkeys*sizeof(u64),
			n->pf);
#endif
	}

	nla_nest_end(skb, nest);

	if (TC_U32_KEY(n->handle))
		if (tcf_exts_dump_stats(skb, &n->exts, &u32_ext_map) < 0)
			goto nla_put_failure;
	return skb->len;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	return -1;
}