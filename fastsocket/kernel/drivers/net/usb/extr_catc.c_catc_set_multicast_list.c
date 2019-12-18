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
struct net_device {int* dev_addr; int flags; int mc_count; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {int /*<<< orphan*/  dmi_addr; struct dev_mc_list* next; } ;
struct catc {int* multicast; int* rxmode; int /*<<< orphan*/  is_f5u011; } ;

/* Variables and functions */
 int AltRxPromisc ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int RxEnable ; 
 int RxMultiCast ; 
 int RxPolarity ; 
 int RxPromisc ; 
 int /*<<< orphan*/  RxUnit ; 
 int /*<<< orphan*/  catc_multicast (int*,int*) ; 
 int /*<<< orphan*/  catc_set_reg_async (struct catc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  catc_write_mem_async (struct catc*,int,int*,int) ; 
 int /*<<< orphan*/  dbg (char*,int,int) ; 
 int ether_crc_le (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f5u011_mchash_async (struct catc*,int*) ; 
 int /*<<< orphan*/  f5u011_rxmode_async (struct catc*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 struct catc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void catc_set_multicast_list(struct net_device *netdev)
{
	struct catc *catc = netdev_priv(netdev);
	struct dev_mc_list *mc;
	u8 broadcast[6];
	u8 rx = RxEnable | RxPolarity | RxMultiCast;
	int i;

	memset(broadcast, 0xff, 6);
	memset(catc->multicast, 0, 64);

	catc_multicast(broadcast, catc->multicast);
	catc_multicast(netdev->dev_addr, catc->multicast);

	if (netdev->flags & IFF_PROMISC) {
		memset(catc->multicast, 0xff, 64);
		rx |= (!catc->is_f5u011) ? RxPromisc : AltRxPromisc;
	} 

	if (netdev->flags & IFF_ALLMULTI) {
		memset(catc->multicast, 0xff, 64);
	} else {
		for (i = 0, mc = netdev->mc_list; mc && i < netdev->mc_count; i++, mc = mc->next) {
			u32 crc = ether_crc_le(6, mc->dmi_addr);
			if (!catc->is_f5u011) {
				catc->multicast[(crc >> 3) & 0x3f] |= 1 << (crc & 7);
			} else {
				catc->multicast[7-(crc >> 29)] |= 1 << ((crc >> 26) & 7);
			}
		}
	}
	if (!catc->is_f5u011) {
		catc_set_reg_async(catc, RxUnit, rx);
		catc_write_mem_async(catc, 0xfa80, catc->multicast, 64);
	} else {
		f5u011_mchash_async(catc, catc->multicast);
		if (catc->rxmode[0] != rx) {
			catc->rxmode[0] = rx;
			dbg("Setting RX mode to %2.2X %2.2X", catc->rxmode[0], catc->rxmode[1]);
			f5u011_rxmode_async(catc, catc->rxmode);
		}
	}
}