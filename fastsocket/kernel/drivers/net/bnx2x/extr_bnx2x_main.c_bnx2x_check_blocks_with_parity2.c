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
struct bnx2x {int dummy; } ;

/* Variables and functions */
#define  AEU_INPUTS_ATTN_BITS_CDU_PARITY_ERROR 135 
#define  AEU_INPUTS_ATTN_BITS_CFC_PARITY_ERROR 134 
#define  AEU_INPUTS_ATTN_BITS_CSEMI_PARITY_ERROR 133 
#define  AEU_INPUTS_ATTN_BITS_DMAE_PARITY_ERROR 132 
#define  AEU_INPUTS_ATTN_BITS_IGU_PARITY_ERROR 131 
#define  AEU_INPUTS_ATTN_BITS_MISC_PARITY_ERROR 130 
#define  AEU_INPUTS_ATTN_BITS_PXP_PARITY_ERROR 129 
#define  AEU_IN_ATTN_BITS_PXPPCICLOCKCLIENT_PARITY_ERROR 128 
 int /*<<< orphan*/  CDU_REG_CDU_PRTY_STS ; 
 int /*<<< orphan*/  CFC_REG_CFC_PRTY_STS ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 int /*<<< orphan*/  CSEM_REG_CSEM_PRTY_STS_0 ; 
 int /*<<< orphan*/  CSEM_REG_CSEM_PRTY_STS_1 ; 
 int /*<<< orphan*/  DMAE_REG_DMAE_PRTY_STS ; 
 int /*<<< orphan*/  HC_REG_HC_PRTY_STS ; 
 int /*<<< orphan*/  IGU_REG_IGU_PRTY_STS ; 
 int /*<<< orphan*/  MISC_REG_MISC_PRTY_STS ; 
 int /*<<< orphan*/  PXP2_REG_PXP2_PRTY_STS_0 ; 
 int /*<<< orphan*/  PXP2_REG_PXP2_PRTY_STS_1 ; 
 int /*<<< orphan*/  PXP_REG_PXP_PRTY_STS ; 
 int /*<<< orphan*/  _print_next_block (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _print_parity (struct bnx2x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_check_blocks_with_parity2(struct bnx2x *bp, u32 sig,
					    int par_num, bool print)
{
	int i = 0;
	u32 cur_bit = 0;
	for (i = 0; sig; i++) {
		cur_bit = ((u32)0x1 << i);
		if (sig & cur_bit) {
			switch (cur_bit) {
			case AEU_INPUTS_ATTN_BITS_CSEMI_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "CSEMI");
					_print_parity(bp,
						      CSEM_REG_CSEM_PRTY_STS_0);
					_print_parity(bp,
						      CSEM_REG_CSEM_PRTY_STS_1);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_PXP_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "PXP");
					_print_parity(bp, PXP_REG_PXP_PRTY_STS);
					_print_parity(bp,
						      PXP2_REG_PXP2_PRTY_STS_0);
					_print_parity(bp,
						      PXP2_REG_PXP2_PRTY_STS_1);
				}
				break;
			case AEU_IN_ATTN_BITS_PXPPCICLOCKCLIENT_PARITY_ERROR:
				if (print)
					_print_next_block(par_num++,
					"PXPPCICLOCKCLIENT");
				break;
			case AEU_INPUTS_ATTN_BITS_CFC_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "CFC");
					_print_parity(bp,
						      CFC_REG_CFC_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_CDU_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "CDU");
					_print_parity(bp, CDU_REG_CDU_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_DMAE_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "DMAE");
					_print_parity(bp,
						      DMAE_REG_DMAE_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_IGU_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "IGU");
					if (CHIP_IS_E1x(bp))
						_print_parity(bp,
							HC_REG_HC_PRTY_STS);
					else
						_print_parity(bp,
							IGU_REG_IGU_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_MISC_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "MISC");
					_print_parity(bp,
						      MISC_REG_MISC_PRTY_STS);
				}
				break;
			}

			/* Clear the bit */
			sig &= ~cur_bit;
		}
	}

	return par_num;
}