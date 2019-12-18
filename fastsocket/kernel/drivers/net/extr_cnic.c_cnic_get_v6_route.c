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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct flowi {int /*<<< orphan*/  oif; int /*<<< orphan*/  fl6_dst; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  fl ;

/* Variables and functions */
 int ENETUNREACH ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int /*<<< orphan*/  init_net ; 
 struct dst_entry* ip6_route_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct flowi*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cnic_get_v6_route(struct sockaddr_in6 *dst_addr,
			     struct dst_entry **dst)
{
#if defined(CONFIG_IPV6) || (defined(CONFIG_IPV6_MODULE) && defined(MODULE))
	struct flowi fl;

	memset(&fl, 0, sizeof(fl));
	ipv6_addr_copy(&fl.fl6_dst, &dst_addr->sin6_addr);
	if (ipv6_addr_type(&fl.fl6_dst) & IPV6_ADDR_LINKLOCAL)
		fl.oif = dst_addr->sin6_scope_id;

	*dst = ip6_route_output(&init_net, NULL, &fl);
	if (*dst)
		return 0;
#endif

	return -ENETUNREACH;
}