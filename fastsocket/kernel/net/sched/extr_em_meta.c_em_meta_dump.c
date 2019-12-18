#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcf_meta_hdr {int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct tcf_ematch {scalar_t__ data; } ;
struct sk_buff {int dummy; } ;
struct meta_type_ops {scalar_t__ (* dump ) (struct sk_buff*,TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  hdr; } ;
struct meta_match {TYPE_1__ rvalue; TYPE_1__ lvalue; } ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_meta_hdr*) ; 
 int /*<<< orphan*/  TCA_EM_META_HDR ; 
 int /*<<< orphan*/  TCA_EM_META_LVALUE ; 
 int /*<<< orphan*/  TCA_EM_META_RVALUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct tcf_meta_hdr*,int /*<<< orphan*/ ,int) ; 
 struct meta_type_ops* meta_type_ops (TYPE_1__*) ; 
 scalar_t__ stub1 (struct sk_buff*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct sk_buff*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em_meta_dump(struct sk_buff *skb, struct tcf_ematch *em)
{
	struct meta_match *meta = (struct meta_match *) em->data;
	struct tcf_meta_hdr hdr;
	struct meta_type_ops *ops;

	memset(&hdr, 0, sizeof(hdr));
	memcpy(&hdr.left, &meta->lvalue.hdr, sizeof(hdr.left));
	memcpy(&hdr.right, &meta->rvalue.hdr, sizeof(hdr.right));

	NLA_PUT(skb, TCA_EM_META_HDR, sizeof(hdr), &hdr);

	ops = meta_type_ops(&meta->lvalue);
	if (ops->dump(skb, &meta->lvalue, TCA_EM_META_LVALUE) < 0 ||
	    ops->dump(skb, &meta->rvalue, TCA_EM_META_RVALUE) < 0)
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -1;
}