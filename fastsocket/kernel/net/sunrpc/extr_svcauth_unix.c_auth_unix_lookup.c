#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net {int dummy; } ;
struct ip_map {scalar_t__ m_add_change; int /*<<< orphan*/  h; TYPE_1__* m_client; } ;
struct in6_addr {int dummy; } ;
struct auth_domain {int /*<<< orphan*/  ref; } ;
struct TYPE_2__ {scalar_t__ addr_changes; struct auth_domain h; } ;

/* Variables and functions */
 scalar_t__ cache_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_map_cache ; 
 struct ip_map* ip_map_lookup (struct net*,char*,struct in6_addr*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunrpc_invalidate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct auth_domain *auth_unix_lookup(struct net *net, struct in6_addr *addr)
{
	struct ip_map *ipm;
	struct auth_domain *rv;

	ipm = ip_map_lookup(net, "nfsd", addr);

	if (!ipm)
		return NULL;
	if (cache_check(&ip_map_cache, &ipm->h, NULL))
		return NULL;

	if ((ipm->m_client->addr_changes - ipm->m_add_change) >0) {
		sunrpc_invalidate(&ipm->h, &ip_map_cache);
		rv = NULL;
	} else {
		rv = &ipm->m_client->h;
		kref_get(&rv->ref);
	}
	cache_put(&ipm->h, &ip_map_cache);
	return rv;
}