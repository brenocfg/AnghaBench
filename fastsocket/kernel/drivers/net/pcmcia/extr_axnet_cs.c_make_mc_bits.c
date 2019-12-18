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
struct net_device {struct dev_mc_list* mc_list; } ;
struct dev_mc_list {int /*<<< orphan*/  dmi_addr; struct dev_mc_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int ether_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void make_mc_bits(u8 *bits, struct net_device *dev)
{
	struct dev_mc_list *dmi;
	u32 crc;

	for (dmi=dev->mc_list; dmi; dmi=dmi->next) {
		
		crc = ether_crc(ETH_ALEN, dmi->dmi_addr);
		/* 
		 * The 8390 uses the 6 most significant bits of the
		 * CRC to index the multicast table.
		 */
		bits[crc>>29] |= (1<<((crc>>26)&7));
	}
}