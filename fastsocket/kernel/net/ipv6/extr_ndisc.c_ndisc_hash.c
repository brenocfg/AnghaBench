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
typedef  int u32 ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct in6_addr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash_rnd; } ;

/* Variables and functions */
 int jhash_2words (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ nd_tbl ; 

__attribute__((used)) static u32 ndisc_hash(const void *pkey, const struct net_device *dev)
{
	const u32 *p32 = pkey;
	u32 addr_hash, i;

	addr_hash = 0;
	for (i = 0; i < (sizeof(struct in6_addr) / sizeof(u32)); i++)
		addr_hash ^= *p32++;

	return jhash_2words(addr_hash, dev->ifindex, nd_tbl.hash_rnd);
}