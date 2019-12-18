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
struct nlattr {int dummy; } ;
struct fib_rule_hdr {scalar_t__ dst_len; scalar_t__ src_len; scalar_t__ tos; } ;
struct fib_rule {scalar_t__ table; scalar_t__ action; } ;
struct dn_fib_table {scalar_t__ n; } ;
struct dn_fib_rule {scalar_t__ dst_len; void* dstmask; scalar_t__ src_len; void* srcmask; void* dst; void* src; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 size_t FRA_DST ; 
 size_t FRA_SRC ; 
 scalar_t__ FR_ACT_TO_TBL ; 
 scalar_t__ RT_TABLE_UNSPEC ; 
 struct dn_fib_table* dn_fib_empty_table () ; 
 void* dnet_make_mask (scalar_t__) ; 
 void* nla_get_le16 (struct nlattr*) ; 

__attribute__((used)) static int dn_fib_rule_configure(struct fib_rule *rule, struct sk_buff *skb,
				 struct fib_rule_hdr *frh,
				 struct nlattr **tb)
{
	int err = -EINVAL;
	struct dn_fib_rule *r = (struct dn_fib_rule *)rule;

	if (frh->tos)
		goto  errout;

	if (rule->table == RT_TABLE_UNSPEC) {
		if (rule->action == FR_ACT_TO_TBL) {
			struct dn_fib_table *table;

			table = dn_fib_empty_table();
			if (table == NULL) {
				err = -ENOBUFS;
				goto errout;
			}

			rule->table = table->n;
		}
	}

	if (frh->src_len)
		r->src = nla_get_le16(tb[FRA_SRC]);

	if (frh->dst_len)
		r->dst = nla_get_le16(tb[FRA_DST]);

	r->src_len = frh->src_len;
	r->srcmask = dnet_make_mask(r->src_len);
	r->dst_len = frh->dst_len;
	r->dstmask = dnet_make_mask(r->dst_len);
	err = 0;
errout:
	return err;
}