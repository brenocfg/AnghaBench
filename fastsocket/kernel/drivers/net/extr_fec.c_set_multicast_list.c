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
struct net_device {int flags; unsigned int mc_count; struct dev_mc_list* mc_list; } ;
struct fec_enet_private {scalar_t__ hwp; } ;
struct dev_mc_list {int* dmi_addr; unsigned int dmi_addrlen; struct dev_mc_list* next; } ;

/* Variables and functions */
 unsigned int CRC32_POLY ; 
 scalar_t__ FEC_GRP_HASH_TABLE_HIGH ; 
 scalar_t__ FEC_GRP_HASH_TABLE_LOW ; 
 scalar_t__ FEC_R_CNTRL ; 
 int HASH_BITS ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void set_multicast_list(struct net_device *dev)
{
	struct fec_enet_private *fep = netdev_priv(dev);
	struct dev_mc_list *dmi;
	unsigned int i, j, bit, data, crc, tmp;
	unsigned char hash;

	if (dev->flags & IFF_PROMISC) {
		tmp = readl(fep->hwp + FEC_R_CNTRL);
		tmp |= 0x8;
		writel(tmp, fep->hwp + FEC_R_CNTRL);
		return;
	}

	tmp = readl(fep->hwp + FEC_R_CNTRL);
	tmp &= ~0x8;
	writel(tmp, fep->hwp + FEC_R_CNTRL);

	if (dev->flags & IFF_ALLMULTI) {
		/* Catch all multicast addresses, so set the
		 * filter to all 1's
		 */
		writel(0xffffffff, fep->hwp + FEC_GRP_HASH_TABLE_HIGH);
		writel(0xffffffff, fep->hwp + FEC_GRP_HASH_TABLE_LOW);

		return;
	}

	/* Clear filter and add the addresses in hash register
	 */
	writel(0, fep->hwp + FEC_GRP_HASH_TABLE_HIGH);
	writel(0, fep->hwp + FEC_GRP_HASH_TABLE_LOW);

	dmi = dev->mc_list;

	for (j = 0; j < dev->mc_count; j++, dmi = dmi->next) {
		/* Only support group multicast for now */
		if (!(dmi->dmi_addr[0] & 1))
			continue;

		/* calculate crc32 value of mac address */
		crc = 0xffffffff;

		for (i = 0; i < dmi->dmi_addrlen; i++) {
			data = dmi->dmi_addr[i];
			for (bit = 0; bit < 8; bit++, data >>= 1) {
				crc = (crc >> 1) ^
				(((crc ^ data) & 1) ? CRC32_POLY : 0);
			}
		}

		/* only upper 6 bits (HASH_BITS) are used
		 * which point to specific bit in he hash registers
		 */
		hash = (crc >> (32 - HASH_BITS)) & 0x3f;

		if (hash > 31) {
			tmp = readl(fep->hwp + FEC_GRP_HASH_TABLE_HIGH);
			tmp |= 1 << (hash - 32);
			writel(tmp, fep->hwp + FEC_GRP_HASH_TABLE_HIGH);
		} else {
			tmp = readl(fep->hwp + FEC_GRP_HASH_TABLE_LOW);
			tmp |= 1 << hash;
			writel(tmp, fep->hwp + FEC_GRP_HASH_TABLE_LOW);
		}
	}
}