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
struct net {int dummy; } ;
struct ip_options {int optlen; int /*<<< orphan*/ * __data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPOPT_END ; 
 scalar_t__ ip_options_compile (struct net*,struct ip_options*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_ip_options (struct ip_options*) ; 

__attribute__((used)) static int ip_options_get_finish(struct net *net, struct ip_options **optp,
				 struct ip_options *opt, int optlen)
{
	while (optlen & 3)
		opt->__data[optlen++] = IPOPT_END;
	opt->optlen = optlen;
	if (optlen && ip_options_compile(net, opt, NULL)) {
		kfree_ip_options(opt);
		return -EINVAL;
	}
	kfree_ip_options(*optp);
	*optp = opt;
	return 0;
}