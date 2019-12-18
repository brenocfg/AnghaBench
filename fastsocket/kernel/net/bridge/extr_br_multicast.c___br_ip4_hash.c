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
typedef  int /*<<< orphan*/  u32 ;
struct net_bridge_mdb_htable {int max; int /*<<< orphan*/  secret; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int jhash_1word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __br_ip4_hash(struct net_bridge_mdb_htable *mdb, __be32 ip)
{
	return jhash_1word(mdb->secret, (u32)ip) & (mdb->max - 1);
}