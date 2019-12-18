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
struct sock {int dummy; } ;
struct ipv6_txoptions {scalar_t__ srcrt; scalar_t__ dst1opt; scalar_t__ dst0opt; scalar_t__ hopopt; int /*<<< orphan*/  tot_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  memcpy (struct ipv6_txoptions*,struct ipv6_txoptions*,int /*<<< orphan*/ ) ; 
 struct ipv6_txoptions* sock_kmalloc (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ipv6_txoptions *
ipv6_dup_options(struct sock *sk, struct ipv6_txoptions *opt)
{
	struct ipv6_txoptions *opt2;

	opt2 = sock_kmalloc(sk, opt->tot_len, GFP_ATOMIC);
	if (opt2) {
		long dif = (char*)opt2 - (char*)opt;
		memcpy(opt2, opt, opt->tot_len);
		if (opt2->hopopt)
			*((char**)&opt2->hopopt) += dif;
		if (opt2->dst0opt)
			*((char**)&opt2->dst0opt) += dif;
		if (opt2->dst1opt)
			*((char**)&opt2->dst1opt) += dif;
		if (opt2->srcrt)
			*((char**)&opt2->srcrt) += dif;
	}
	return opt2;
}