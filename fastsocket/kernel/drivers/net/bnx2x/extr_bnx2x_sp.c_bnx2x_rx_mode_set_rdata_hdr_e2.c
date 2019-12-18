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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct eth_classify_header {int /*<<< orphan*/  rule_cnt; int /*<<< orphan*/  echo; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bnx2x_rx_mode_set_rdata_hdr_e2(u32 cid,
				struct eth_classify_header *hdr,
				u8 rule_cnt)
{
	hdr->echo = cpu_to_le32(cid);
	hdr->rule_cnt = rule_cnt;
}