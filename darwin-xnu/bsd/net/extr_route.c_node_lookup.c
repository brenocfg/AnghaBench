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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int sa_family; } ;
struct radix_node_head {struct radix_node* (* rnh_lookup_args ) (struct sockaddr*,struct sockaddr*,struct radix_node_head*,int /*<<< orphan*/ *,void*) ;} ;
struct radix_node {int rn_flags; } ;
struct matchleaf_arg {unsigned int member_0; } ;
typedef  int /*<<< orphan*/  rn_matchf_t ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 unsigned int IFSCOPE_NONE ; 
 int RNF_ROOT ; 
 struct sockaddr* ma_copy (int,struct sockaddr*,struct sockaddr_storage*,unsigned int) ; 
 int /*<<< orphan*/ * rn_match_ifscope ; 
 struct radix_node_head** rt_tables ; 
 struct sockaddr* sa_copy (struct sockaddr*,struct sockaddr_storage*,unsigned int*) ; 
 struct radix_node* stub1 (struct sockaddr*,struct sockaddr*,struct radix_node_head*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static struct radix_node *
node_lookup(struct sockaddr *dst, struct sockaddr *netmask,
    unsigned int ifscope)
{
	struct radix_node_head *rnh;
	struct radix_node *rn;
	struct sockaddr_storage ss, mask;
	int af = dst->sa_family;
	struct matchleaf_arg ma = { ifscope };
	rn_matchf_t *f = rn_match_ifscope;
	void *w = &ma;

	if (af != AF_INET && af != AF_INET6)
		return (NULL);

	rnh = rt_tables[af];

	/*
	 * Transform dst into the internal routing table form,
	 * clearing out the scope ID field if ifscope isn't set.
	 */
	dst = sa_copy(dst, &ss, (ifscope == IFSCOPE_NONE) ? NULL : &ifscope);

	/* Transform netmask into the internal routing table form */
	if (netmask != NULL)
		netmask = ma_copy(af, netmask, &mask, ifscope);

	if (ifscope == IFSCOPE_NONE)
		f = w = NULL;

	rn = rnh->rnh_lookup_args(dst, netmask, rnh, f, w);
	if (rn != NULL && (rn->rn_flags & RNF_ROOT))
		rn = NULL;

	return (rn);
}