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
struct crc_pair {scalar_t__ size; int /*<<< orphan*/  offset; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_MSG_ETHTOOL ; 
 int BNX2X_MSG_NVM ; 
 int /*<<< orphan*/  DP (int,char*,int,int) ; 
 int bnx2x_nvram_crc (struct bnx2x*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2x_test_nvram_tbl(struct bnx2x *bp,
				const struct crc_pair *nvram_tbl, u8 *buf)
{
	int i;

	for (i = 0; nvram_tbl[i].size; i++) {
		int rc = bnx2x_nvram_crc(bp, nvram_tbl[i].offset,
					 nvram_tbl[i].size, buf);
		if (rc) {
			DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
			   "nvram_tbl[%d] has failed crc test (rc %d)\n",
			   i, rc);
			return rc;
		}
	}

	return 0;
}