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
typedef  int uint8_t ;
struct xt_mtchk_param {struct ebt_entry* entryinfo; struct ebt_stp_info* matchinfo; } ;
struct ebt_stp_info {int bitmask; int invflags; } ;
struct ebt_entry {int bitmask; int /*<<< orphan*/  destmsk; int /*<<< orphan*/  destmac; } ;

/* Variables and functions */
 int EBT_DESTMAC ; 
 int EBT_STP_MASK ; 
 scalar_t__ compare_ether_addr (int /*<<< orphan*/ ,int const*) ; 

__attribute__((used)) static bool ebt_stp_mt_check(const struct xt_mtchk_param *par)
{
	const struct ebt_stp_info *info = par->matchinfo;
	const uint8_t bridge_ula[6] = {0x01, 0x80, 0xc2, 0x00, 0x00, 0x00};
	const uint8_t msk[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	const struct ebt_entry *e = par->entryinfo;

	if (info->bitmask & ~EBT_STP_MASK || info->invflags & ~EBT_STP_MASK ||
	    !(info->bitmask & EBT_STP_MASK))
		return false;
	/* Make sure the match only receives stp frames */
	if (compare_ether_addr(e->destmac, bridge_ula) ||
	    compare_ether_addr(e->destmsk, msk) || !(e->bitmask & EBT_DESTMAC))
		return false;

	return true;
}