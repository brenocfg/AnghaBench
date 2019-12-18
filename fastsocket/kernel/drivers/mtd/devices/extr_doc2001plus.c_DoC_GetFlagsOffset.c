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
struct mtd_info {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 unsigned int NAND_CMD_READ1 ; 

__attribute__((used)) static unsigned int DoC_GetFlagsOffset(struct mtd_info *mtd, loff_t *from)
{
	unsigned int ofs, cmd;

	cmd = NAND_CMD_READ1;
	ofs = (*from & 0x200) ? 8 : 6;
	*from = (*from & ~0x3ff) | ofs;
	return cmd;
}