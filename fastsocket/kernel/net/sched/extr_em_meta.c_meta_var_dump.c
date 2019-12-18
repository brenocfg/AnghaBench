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
struct sk_buff {int dummy; } ;
struct meta_value {scalar_t__ val; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int,scalar_t__,void*) ; 

__attribute__((used)) static int meta_var_dump(struct sk_buff *skb, struct meta_value *v, int tlv)
{
	if (v->val && v->len)
		NLA_PUT(skb, tlv, v->len, (void *) v->val);
	return 0;

nla_put_failure:
	return -1;
}