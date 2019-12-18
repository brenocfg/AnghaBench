#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tcf_pkt_info {int dummy; } ;
struct tcf_ematch {scalar_t__ data; } ;
struct sk_buff {int dummy; } ;
struct meta_obj {int dummy; } ;
struct TYPE_5__ {int op; } ;
struct TYPE_7__ {TYPE_1__ hdr; } ;
struct meta_match {TYPE_3__ lvalue; TYPE_3__ rvalue; } ;
struct TYPE_6__ {int (* compare ) (struct meta_obj*,struct meta_obj*) ;} ;

/* Variables and functions */
#define  TCF_EM_OPND_EQ 130 
#define  TCF_EM_OPND_GT 129 
#define  TCF_EM_OPND_LT 128 
 scalar_t__ meta_get (struct sk_buff*,struct tcf_pkt_info*,TYPE_3__*,struct meta_obj*) ; 
 TYPE_2__* meta_type_ops (TYPE_3__*) ; 
 int stub1 (struct meta_obj*,struct meta_obj*) ; 

__attribute__((used)) static int em_meta_match(struct sk_buff *skb, struct tcf_ematch *m,
			 struct tcf_pkt_info *info)
{
	int r;
	struct meta_match *meta = (struct meta_match *) m->data;
	struct meta_obj l_value, r_value;

	if (meta_get(skb, info, &meta->lvalue, &l_value) < 0 ||
	    meta_get(skb, info, &meta->rvalue, &r_value) < 0)
		return 0;

	r = meta_type_ops(&meta->lvalue)->compare(&l_value, &r_value);

	switch (meta->lvalue.hdr.op) {
		case TCF_EM_OPND_EQ:
			return !r;
		case TCF_EM_OPND_LT:
			return r < 0;
		case TCF_EM_OPND_GT:
			return r > 0;
	}

	return 0;
}