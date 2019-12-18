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
struct flowi {int fld_dst; int fld_src; } ;
struct fib_rule {int dummy; } ;
struct dn_fib_rule {int src; int srcmask; int dst; int dstmask; } ;
typedef  int __le16 ;

/* Variables and functions */

__attribute__((used)) static int dn_fib_rule_match(struct fib_rule *rule, struct flowi *fl, int flags)
{
	struct dn_fib_rule *r = (struct dn_fib_rule *)rule;
	__le16 daddr = fl->fld_dst;
	__le16 saddr = fl->fld_src;

	if (((saddr ^ r->src) & r->srcmask) ||
	    ((daddr ^ r->dst) & r->dstmask))
		return 0;

	return 1;
}