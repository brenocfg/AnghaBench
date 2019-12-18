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
typedef  int u32 ;
struct davinci_nand_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_4BIT_ECC1_OFFSET ; 
 int /*<<< orphan*/  NAND_4BIT_ECC2_OFFSET ; 
 int /*<<< orphan*/  NAND_4BIT_ECC3_OFFSET ; 
 int /*<<< orphan*/  NAND_4BIT_ECC4_OFFSET ; 
 int const davinci_nand_readl (struct davinci_nand_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nand_davinci_readecc_4bit(struct davinci_nand_info *info, u32 code[4])
{
	const u32 mask = 0x03ff03ff;

	code[0] = davinci_nand_readl(info, NAND_4BIT_ECC1_OFFSET) & mask;
	code[1] = davinci_nand_readl(info, NAND_4BIT_ECC2_OFFSET) & mask;
	code[2] = davinci_nand_readl(info, NAND_4BIT_ECC3_OFFSET) & mask;
	code[3] = davinci_nand_readl(info, NAND_4BIT_ECC4_OFFSET) & mask;
}