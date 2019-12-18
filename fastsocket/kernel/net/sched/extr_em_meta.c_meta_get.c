#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcf_pkt_info {int dummy; } ;
struct sk_buff {int dummy; } ;
struct meta_value {int /*<<< orphan*/  len; int /*<<< orphan*/  val; } ;
struct meta_obj {int /*<<< orphan*/  len; int /*<<< orphan*/  value; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get ) (struct sk_buff*,struct tcf_pkt_info*,struct meta_value*,struct meta_obj*,int*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* apply_extras ) (struct meta_value*,struct meta_obj*) ;} ;

/* Variables and functions */
 scalar_t__ TCF_META_ID_VALUE ; 
 scalar_t__ meta_id (struct meta_value*) ; 
 TYPE_2__* meta_ops (struct meta_value*) ; 
 TYPE_1__* meta_type_ops (struct meta_value*) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,struct tcf_pkt_info*,struct meta_value*,struct meta_obj*,int*) ; 
 int /*<<< orphan*/  stub2 (struct meta_value*,struct meta_obj*) ; 

__attribute__((used)) static int meta_get(struct sk_buff *skb, struct tcf_pkt_info *info,
		    struct meta_value *v, struct meta_obj *dst)
{
	int err = 0;

	if (meta_id(v) == TCF_META_ID_VALUE) {
		dst->value = v->val;
		dst->len = v->len;
		return 0;
	}

	meta_ops(v)->get(skb, info, v, dst, &err);
	if (err < 0)
		return err;

	if (meta_type_ops(v)->apply_extras)
	    meta_type_ops(v)->apply_extras(v, dst);

	return 0;
}