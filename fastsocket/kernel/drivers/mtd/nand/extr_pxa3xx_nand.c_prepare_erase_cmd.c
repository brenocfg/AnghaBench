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
typedef  int uint16_t ;
struct pxa3xx_nand_info {int ndcb0; int ndcb1; scalar_t__ ndcb2; } ;

/* Variables and functions */
 int NDCB0_ADDR_CYC (int) ; 
 int NDCB0_AUTO_RS ; 
 int NDCB0_CMD_TYPE (int) ; 
 int NDCB0_DBC ; 

__attribute__((used)) static int prepare_erase_cmd(struct pxa3xx_nand_info *info,
			uint16_t cmd, int page_addr)
{
	info->ndcb0 = cmd | ((cmd & 0xff00) ? NDCB0_DBC : 0);
	info->ndcb0 |= NDCB0_CMD_TYPE(2) | NDCB0_AUTO_RS | NDCB0_ADDR_CYC(3);
	info->ndcb1 = page_addr;
	info->ndcb2 = 0;
	return 0;
}