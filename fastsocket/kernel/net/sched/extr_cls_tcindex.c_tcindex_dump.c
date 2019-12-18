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
struct tcmsg {int tcm_handle; } ;
struct TYPE_2__ {int classid; scalar_t__ class; } ;
struct tcindex_filter_result {int /*<<< orphan*/  exts; TYPE_1__ res; } ;
struct tcindex_filter {int key; struct tcindex_filter_result result; struct tcindex_filter* next; } ;
struct tcindex_data {int hash; int shift; int fall_through; struct tcindex_filter** h; struct tcindex_filter_result* perfect; int /*<<< orphan*/  mask; } ;
struct tcf_proto {int dummy; } ;
struct sk_buff {int len; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT_U16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct tcindex_data* PRIV (struct tcf_proto*) ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  TCA_TCINDEX_CLASSID ; 
 int /*<<< orphan*/  TCA_TCINDEX_FALL_THROUGH ; 
 int /*<<< orphan*/  TCA_TCINDEX_HASH ; 
 int /*<<< orphan*/  TCA_TCINDEX_MASK ; 
 int /*<<< orphan*/  TCA_TCINDEX_SHIFT ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 scalar_t__ tcf_exts_dump (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tcf_exts_dump_stats (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcindex_ext_map ; 

__attribute__((used)) static int tcindex_dump(struct tcf_proto *tp, unsigned long fh,
    struct sk_buff *skb, struct tcmsg *t)
{
	struct tcindex_data *p = PRIV(tp);
	struct tcindex_filter_result *r = (struct tcindex_filter_result *) fh;
	unsigned char *b = skb_tail_pointer(skb);
	struct nlattr *nest;

	pr_debug("tcindex_dump(tp %p,fh 0x%lx,skb %p,t %p),p %p,r %p,b %p\n",
		 tp, fh, skb, t, p, r, b);
	pr_debug("p->perfect %p p->h %p\n", p->perfect, p->h);

	nest = nla_nest_start(skb, TCA_OPTIONS);
	if (nest == NULL)
		goto nla_put_failure;

	if (!fh) {
		t->tcm_handle = ~0; /* whatever ... */
		NLA_PUT_U32(skb, TCA_TCINDEX_HASH, p->hash);
		NLA_PUT_U16(skb, TCA_TCINDEX_MASK, p->mask);
		NLA_PUT_U32(skb, TCA_TCINDEX_SHIFT, p->shift);
		NLA_PUT_U32(skb, TCA_TCINDEX_FALL_THROUGH, p->fall_through);
		nla_nest_end(skb, nest);
	} else {
		if (p->perfect) {
			t->tcm_handle = r-p->perfect;
		} else {
			struct tcindex_filter *f;
			int i;

			t->tcm_handle = 0;
			for (i = 0; !t->tcm_handle && i < p->hash; i++) {
				for (f = p->h[i]; !t->tcm_handle && f;
				     f = f->next) {
					if (&f->result == r)
						t->tcm_handle = f->key;
				}
			}
		}
		pr_debug("handle = %d\n", t->tcm_handle);
		if (r->res.class)
			NLA_PUT_U32(skb, TCA_TCINDEX_CLASSID, r->res.classid);

		if (tcf_exts_dump(skb, &r->exts, &tcindex_ext_map) < 0)
			goto nla_put_failure;
		nla_nest_end(skb, nest);

		if (tcf_exts_dump_stats(skb, &r->exts, &tcindex_ext_map) < 0)
			goto nla_put_failure;
	}

	return skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	return -1;
}