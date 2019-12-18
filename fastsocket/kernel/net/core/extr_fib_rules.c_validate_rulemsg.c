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
struct nlattr {int dummy; } ;
struct fib_rules_ops {int addr_size; } ;
struct fib_rule_hdr {int src_len; int dst_len; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t FRA_DST ; 
 size_t FRA_SRC ; 
 int nla_len (struct nlattr*) ; 

__attribute__((used)) static int validate_rulemsg(struct fib_rule_hdr *frh, struct nlattr **tb,
			    struct fib_rules_ops *ops)
{
	int err = -EINVAL;

	if (frh->src_len)
		if (tb[FRA_SRC] == NULL ||
		    frh->src_len > (ops->addr_size * 8) ||
		    nla_len(tb[FRA_SRC]) != ops->addr_size)
			goto errout;

	if (frh->dst_len)
		if (tb[FRA_DST] == NULL ||
		    frh->dst_len > (ops->addr_size * 8) ||
		    nla_len(tb[FRA_DST]) != ops->addr_size)
			goto errout;

	err = 0;
errout:
	return err;
}