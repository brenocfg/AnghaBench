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
struct net_bridge_mdb_htable {int dummy; } ;
struct net_bridge_mdb_entry {int dummy; } ;
struct br_ip {int dummy; } ;

/* Variables and functions */
 struct net_bridge_mdb_entry* __br_mdb_ip_get (struct net_bridge_mdb_htable*,struct br_ip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_ip_hash (struct net_bridge_mdb_htable*,struct br_ip*) ; 

__attribute__((used)) static struct net_bridge_mdb_entry *br_mdb_ip_get(
	struct net_bridge_mdb_htable *mdb, struct br_ip *dst)
{
	if (!mdb)
		return NULL;

	return __br_mdb_ip_get(mdb, dst, br_ip_hash(mdb, dst));
}