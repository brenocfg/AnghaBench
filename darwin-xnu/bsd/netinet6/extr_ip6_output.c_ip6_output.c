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
struct route_in6 {int dummy; } ;
struct mbuf {int dummy; } ;
struct ip6_pktopts {int dummy; } ;
struct ip6_out_args {int dummy; } ;
struct ip6_moptions {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int ip6_output_list (struct mbuf*,int /*<<< orphan*/ ,struct ip6_pktopts*,struct route_in6*,int,struct ip6_moptions*,struct ifnet**,struct ip6_out_args*) ; 

int
ip6_output(struct mbuf *m0, struct ip6_pktopts *opt,
    struct route_in6 *ro, int flags, struct ip6_moptions *im6o,
    struct ifnet **ifpp, struct ip6_out_args *ip6oa)
{
	return ip6_output_list(m0, 0, opt, ro, flags, im6o, ifpp, ip6oa);
}