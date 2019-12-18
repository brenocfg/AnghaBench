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
#define  AEU_INPUTS_ATTN_BITS_CCM_PARITY_ERROR 143 
#define  AEU_INPUTS_ATTN_BITS_CSDM_PARITY_ERROR 142 
#define  AEU_INPUTS_ATTN_BITS_DEBUG_PARITY_ERROR 141 
#define  AEU_INPUTS_ATTN_BITS_DOORBELLQ_PARITY_ERROR 140 
#define  AEU_INPUTS_ATTN_BITS_NIG_PARITY_ERROR 139 
#define  AEU_INPUTS_ATTN_BITS_PBF_PARITY_ERROR 138 
#define  AEU_INPUTS_ATTN_BITS_QM_PARITY_ERROR 137 
#define  AEU_INPUTS_ATTN_BITS_TIMERS_PARITY_ERROR 136 
#define  AEU_INPUTS_ATTN_BITS_UCM_PARITY_ERROR 135 
#define  AEU_INPUTS_ATTN_BITS_UPB_PARITY_ERROR 134 
#define  AEU_INPUTS_ATTN_BITS_USDM_PARITY_ERROR 133 
#define  AEU_INPUTS_ATTN_BITS_USEMI_PARITY_ERROR 132 
#define  AEU_INPUTS_ATTN_BITS_VAUX_PCI_CORE_PARITY_ERROR 131 
#define  AEU_INPUTS_ATTN_BITS_XCM_PARITY_ERROR 130 
#define  AEU_INPUTS_ATTN_BITS_XSDM_PARITY_ERROR 129 
#define  AEU_INPUTS_ATTN_BITS_XSEMI_PARITY_ERROR 128 
 scalar_t__ CCM_REG_CCM_PRTY_STS ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 scalar_t__ CSDM_REG_CSDM_PRTY_STS ; 
 scalar_t__ DBG_REG_DBG_PRTY_STS ; 
 scalar_t__ DORQ_REG_DORQ_PRTY_STS ; 
 scalar_t__ GRCBASE_UPB ; 
 scalar_t__ NIG_REG_NIG_PRTY_STS ; 
 scalar_t__ NIG_REG_NIG_PRTY_STS_0 ; 
 scalar_t__ NIG_REG_NIG_PRTY_STS_1 ; 
 scalar_t__ PBF_REG_PBF_PRTY_STS ; 
 scalar_t__ PB_REG_PB_PRTY_STS ; 
 scalar_t__ QM_REG_QM_PRTY_STS ; 
 scalar_t__ TM_REG_TM_PRTY_STS ; 
 scalar_t__ UCM_REG_UCM_PRTY_STS ; 
 scalar_t__ USDM_REG_USDM_PRTY_STS ; 
 scalar_t__ USEM_REG_USEM_PRTY_STS_0 ; 
 scalar_t__ USEM_REG_USEM_PRTY_STS_1 ; 
 scalar_t__ XCM_REG_XCM_PRTY_STS ; 
 scalar_t__ XSDM_REG_XSDM_PRTY_STS ; 
 scalar_t__ XSEM_REG_XSEM_PRTY_STS_0 ; 
 scalar_t__ XSEM_REG_XSEM_PRTY_STS_1 ; 
 int /*<<< orphan*/  _print_next_block (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _print_parity (struct bnx2x*,scalar_t__) ; 

__attribute__((used)) static int bnx2x_check_blocks_with_parity1(struct bnx2x *bp, u32 sig,
					    int par_num, bool *global,
					    bool print)
{
	int i = 0;
	u32 cur_bit = 0;
	for (i = 0; sig; i++) {
		cur_bit = ((u32)0x1 << i);
		if (sig & cur_bit) {
			switch (cur_bit) {
			case AEU_INPUTS_ATTN_BITS_PBF_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "PBF");
					_print_parity(bp, PBF_REG_PBF_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_QM_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "QM");
					_print_parity(bp, QM_REG_QM_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_TIMERS_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "TM");
					_print_parity(bp, TM_REG_TM_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_XSDM_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "XSDM");
					_print_parity(bp,
						      XSDM_REG_XSDM_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_XCM_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "XCM");
					_print_parity(bp, XCM_REG_XCM_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_XSEMI_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "XSEMI");
					_print_parity(bp,
						      XSEM_REG_XSEM_PRTY_STS_0);
					_print_parity(bp,
						      XSEM_REG_XSEM_PRTY_STS_1);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_DOORBELLQ_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++,
							  "DOORBELLQ");
					_print_parity(bp,
						      DORQ_REG_DORQ_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_NIG_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "NIG");
					if (CHIP_IS_E1x(bp)) {
						_print_parity(bp,
							NIG_REG_NIG_PRTY_STS);
					} else {
						_print_parity(bp,
							NIG_REG_NIG_PRTY_STS_0);
						_print_parity(bp,
							NIG_REG_NIG_PRTY_STS_1);
					}
				}
				break;
			case AEU_INPUTS_ATTN_BITS_VAUX_PCI_CORE_PARITY_ERROR:
				if (print)
					_print_next_block(par_num++,
							  "VAUX PCI CORE");
				*global = true;
				break;
			case AEU_INPUTS_ATTN_BITS_DEBUG_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "DEBUG");
					_print_parity(bp, DBG_REG_DBG_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_USDM_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "USDM");
					_print_parity(bp,
						      USDM_REG_USDM_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_UCM_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "UCM");
					_print_parity(bp, UCM_REG_UCM_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_USEMI_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "USEMI");
					_print_parity(bp,
						      USEM_REG_USEM_PRTY_STS_0);
					_print_parity(bp,
						      USEM_REG_USEM_PRTY_STS_1);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_UPB_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "UPB");
					_print_parity(bp, GRCBASE_UPB +
							  PB_REG_PB_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_CSDM_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "CSDM");
					_print_parity(bp,
						      CSDM_REG_CSDM_PRTY_STS);
				}
				break;
			case AEU_INPUTS_ATTN_BITS_CCM_PARITY_ERROR:
				if (print) {
					_print_next_block(par_num++, "CCM");
					_print_parity(bp, CCM_REG_CCM_PRTY_STS);
				}
				break;
			}

			/* Clear the bit */
			sig &= ~cur_bit;
		}
	}

	return par_num;
}