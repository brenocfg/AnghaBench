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
typedef  int u16 ;
struct mcast_address {struct mcast_address* next; int /*<<< orphan*/  address; } ;
struct ether_header {int* ether_dhost; } ;
struct TYPE_2__ {int /*<<< orphan*/  multicast; } ;
struct adapter {int macopts; int /*<<< orphan*/  rcv_unicasts; TYPE_1__ stats; int /*<<< orphan*/  rcv_multicasts; struct mcast_address* mcastaddrs; int /*<<< orphan*/  rcv_broadcasts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_EQ_ADDR (int /*<<< orphan*/ ,int*,int) ; 
 int MAC_ALLMCAST ; 
 int MAC_BCAST ; 
 int MAC_DIRECTED ; 
 int MAC_MCAST ; 
 int MAC_PROMISC ; 

__attribute__((used)) static bool slic_mac_filter(struct adapter *adapter,
			struct ether_header *ether_frame)
{
	u32 opts = adapter->macopts;
	u32 *dhost4 = (u32 *)&ether_frame->ether_dhost[0];
	u16 *dhost2 = (u16 *)&ether_frame->ether_dhost[4];
	bool equaladdr;

	if (opts & MAC_PROMISC)
		return true;

	if ((*dhost4 == 0xFFFFFFFF) && (*dhost2 == 0xFFFF)) {
		if (opts & MAC_BCAST) {
			adapter->rcv_broadcasts++;
			return true;
		} else {
			return false;
		}
	}

	if (ether_frame->ether_dhost[0] & 0x01) {
		if (opts & MAC_ALLMCAST) {
			adapter->rcv_multicasts++;
			adapter->stats.multicast++;
			return true;
		}
		if (opts & MAC_MCAST) {
			struct mcast_address *mcaddr = adapter->mcastaddrs;

			while (mcaddr) {
				ETHER_EQ_ADDR(mcaddr->address,
					      ether_frame->ether_dhost,
					      equaladdr);
				if (equaladdr) {
					adapter->rcv_multicasts++;
					adapter->stats.multicast++;
					return true;
				}
				mcaddr = mcaddr->next;
			}
			return false;
		} else {
			return false;
		}
	}
	if (opts & MAC_DIRECTED) {
		adapter->rcv_unicasts++;
		return true;
	}
	return false;

}