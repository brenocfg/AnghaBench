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
struct xt_mtchk_param {struct ebt_entry* entryinfo; struct ebt_vlan_info* matchinfo; } ;
struct ebt_vlan_info {int bitmask; int invflags; unsigned short id; unsigned short prio; scalar_t__ encap; } ;
struct ebt_entry {scalar_t__ ethproto; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MSG (char*,unsigned short,...) ; 
 int EBT_VLAN_ENCAP ; 
 int EBT_VLAN_ID ; 
 int EBT_VLAN_MASK ; 
 int EBT_VLAN_PRIO ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 unsigned short ETH_ZLEN ; 
 scalar_t__ GET_BITMASK (int) ; 
 unsigned short VLAN_GROUP_ARRAY_LEN ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 unsigned short ntohs (scalar_t__) ; 

__attribute__((used)) static bool ebt_vlan_mt_check(const struct xt_mtchk_param *par)
{
	struct ebt_vlan_info *info = par->matchinfo;
	const struct ebt_entry *e = par->entryinfo;

	/* Is it 802.1Q frame checked? */
	if (e->ethproto != htons(ETH_P_8021Q)) {
		DEBUG_MSG
		    ("passed entry proto %2.4X is not 802.1Q (8100)\n",
		     (unsigned short) ntohs(e->ethproto));
		return false;
	}

	/* Check for bitmask range
	 * True if even one bit is out of mask */
	if (info->bitmask & ~EBT_VLAN_MASK) {
		DEBUG_MSG("bitmask %2X is out of mask (%2X)\n",
			  info->bitmask, EBT_VLAN_MASK);
		return false;
	}

	/* Check for inversion flags range */
	if (info->invflags & ~EBT_VLAN_MASK) {
		DEBUG_MSG("inversion flags %2X is out of mask (%2X)\n",
			  info->invflags, EBT_VLAN_MASK);
		return false;
	}

	/* Reserved VLAN ID (VID) values
	 * -----------------------------
	 * 0 - The null VLAN ID.
	 * 1 - The default Port VID (PVID)
	 * 0x0FFF - Reserved for implementation use.
	 * if_vlan.h: VLAN_GROUP_ARRAY_LEN 4096. */
	if (GET_BITMASK(EBT_VLAN_ID)) {
		if (!!info->id) { /* if id!=0 => check vid range */
			if (info->id > VLAN_GROUP_ARRAY_LEN) {
				DEBUG_MSG
				    ("id %d is out of range (1-4096)\n",
				     info->id);
				return false;
			}
			/* Note: This is valid VLAN-tagged frame point.
			 * Any value of user_priority are acceptable,
			 * but should be ignored according to 802.1Q Std.
			 * So we just drop the prio flag. */
			info->bitmask &= ~EBT_VLAN_PRIO;
		}
		/* Else, id=0 (null VLAN ID)  => user_priority range (any?) */
	}

	if (GET_BITMASK(EBT_VLAN_PRIO)) {
		if ((unsigned char) info->prio > 7) {
			DEBUG_MSG("prio %d is out of range (0-7)\n",
			     info->prio);
			return false;
		}
	}
	/* Check for encapsulated proto range - it is possible to be
	 * any value for u_short range.
	 * if_ether.h:  ETH_ZLEN        60   -  Min. octets in frame sans FCS */
	if (GET_BITMASK(EBT_VLAN_ENCAP)) {
		if ((unsigned short) ntohs(info->encap) < ETH_ZLEN) {
			DEBUG_MSG
			    ("encap frame length %d is less than minimal\n",
			     ntohs(info->encap));
			return false;
		}
	}

	return true;
}