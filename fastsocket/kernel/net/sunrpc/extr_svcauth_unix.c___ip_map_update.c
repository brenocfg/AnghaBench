#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct unix_domain {int /*<<< orphan*/  addr_changes; } ;
struct TYPE_3__ {scalar_t__ expiry_time; scalar_t__ flags; } ;
struct ip_map {int /*<<< orphan*/  m_addr; int /*<<< orphan*/  m_class; TYPE_1__ h; int /*<<< orphan*/  m_add_change; struct unix_domain* m_client; } ;
struct cache_head {int dummy; } ;
struct cache_detail {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_NEGATIVE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IP_HASHBITS ; 
 scalar_t__ NEVER ; 
 int /*<<< orphan*/  cache_put (struct cache_head*,struct cache_detail*) ; 
 int hash_ip6 (int /*<<< orphan*/ ) ; 
 int hash_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 struct cache_head* sunrpc_cache_update (struct cache_detail*,TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static int __ip_map_update(struct cache_detail *cd, struct ip_map *ipm,
		struct unix_domain *udom, time_t expiry)
{
	struct ip_map ip;
	struct cache_head *ch;

	ip.m_client = udom;
	ip.h.flags = 0;
	if (!udom)
		set_bit(CACHE_NEGATIVE, &ip.h.flags);
	else {
		ip.m_add_change = udom->addr_changes;
		/* if this is from the legacy set_client system call,
		 * we need m_add_change to be one higher
		 */
		if (expiry == NEVER)
			ip.m_add_change++;
	}
	ip.h.expiry_time = expiry;
	ch = sunrpc_cache_update(cd, &ip.h, &ipm->h,
				 hash_str(ipm->m_class, IP_HASHBITS) ^
				 hash_ip6(ipm->m_addr));
	if (!ch)
		return -ENOMEM;
	cache_put(ch, cd);
	return 0;
}