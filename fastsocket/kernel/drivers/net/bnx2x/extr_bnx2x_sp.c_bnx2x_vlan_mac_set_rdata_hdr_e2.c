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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct eth_classify_header {scalar_t__ rule_cnt; int /*<<< orphan*/  echo; } ;

/* Variables and functions */
 int BNX2X_SWCID_MASK ; 
 int BNX2X_SWCID_SHIFT ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static inline void bnx2x_vlan_mac_set_rdata_hdr_e2(u32 cid, int type,
				struct eth_classify_header *hdr, int rule_cnt)
{
	hdr->echo = cpu_to_le32((cid & BNX2X_SWCID_MASK) |
				(type << BNX2X_SWCID_SHIFT));
	hdr->rule_cnt = (u8)rule_cnt;
}