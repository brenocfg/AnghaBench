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
typedef  int u8 ;
typedef  int u32 ;
struct net_device {int flags; struct dev_addr_list* mc_list; } ;
struct mv643xx_eth_private {int port_num; } ;
struct dev_addr_list {int* da_addr; struct dev_addr_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ OTHER_MCAST_TABLE (int) ; 
 scalar_t__ SPECIAL_MCAST_TABLE (int) ; 
 int addr_crc (int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int*,char*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wrl (struct mv643xx_eth_private*,scalar_t__,int) ; 

__attribute__((used)) static void mv643xx_eth_program_multicast_filter(struct net_device *dev)
{
	struct mv643xx_eth_private *mp = netdev_priv(dev);
	u32 *mc_spec;
	u32 *mc_other;
	struct dev_addr_list *addr;
	int i;

	if (dev->flags & (IFF_PROMISC | IFF_ALLMULTI)) {
		int port_num;
		u32 accept;

oom:
		port_num = mp->port_num;
		accept = 0x01010101;
		for (i = 0; i < 0x100; i += 4) {
			wrl(mp, SPECIAL_MCAST_TABLE(port_num) + i, accept);
			wrl(mp, OTHER_MCAST_TABLE(port_num) + i, accept);
		}
		return;
	}

	mc_spec = kmalloc(0x200, GFP_ATOMIC);
	if (mc_spec == NULL)
		goto oom;
	mc_other = mc_spec + (0x100 >> 2);

	memset(mc_spec, 0, 0x100);
	memset(mc_other, 0, 0x100);

	for (addr = dev->mc_list; addr != NULL; addr = addr->next) {
		u8 *a = addr->da_addr;
		u32 *table;
		int entry;

		if (memcmp(a, "\x01\x00\x5e\x00\x00", 5) == 0) {
			table = mc_spec;
			entry = a[5];
		} else {
			table = mc_other;
			entry = addr_crc(a);
		}

		table[entry >> 2] |= 1 << (8 * (entry & 3));
	}

	for (i = 0; i < 0x100; i += 4) {
		wrl(mp, SPECIAL_MCAST_TABLE(mp->port_num) + i, mc_spec[i >> 2]);
		wrl(mp, OTHER_MCAST_TABLE(mp->port_num) + i, mc_other[i >> 2]);
	}

	kfree(mc_spec);
}