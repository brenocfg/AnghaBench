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
typedef  int uint32_t ;
struct sh_flctl {int erase_ADRCNT; int rw_ADRCNT; scalar_t__ page_size; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int ADRCNT_1 ; 
 int CDSRC_E ; 
 int DOADR_E ; 
 int DOCMD1_E ; 
 int DOCMD2_E ; 
 int DOSR_E ; 
 int /*<<< orphan*/  FLCMCDR (struct sh_flctl*) ; 
 int /*<<< orphan*/  FLCMDCR (struct sh_flctl*) ; 
 int /*<<< orphan*/  FLCMNCR (struct sh_flctl*) ; 
#define  NAND_CMD_ERASE1 135 
#define  NAND_CMD_PAGEPROG 134 
#define  NAND_CMD_READ0 133 
#define  NAND_CMD_READID 132 
#define  NAND_CMD_READOOB 131 
#define  NAND_CMD_RESET 130 
#define  NAND_CMD_SEQIN 129 
#define  NAND_CMD_STATUS 128 
 int SELRW ; 
 int SNAND_E ; 
 struct sh_flctl* mtd_to_flctl (struct mtd_info*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_cmd_regs(struct mtd_info *mtd, uint32_t cmd, uint32_t flcmcdr_val)
{
	struct sh_flctl *flctl = mtd_to_flctl(mtd);
	uint32_t flcmncr_val = readl(FLCMNCR(flctl));
	uint32_t flcmdcr_val, addr_len_bytes = 0;

	/* Set SNAND bit if page size is 2048byte */
	if (flctl->page_size)
		flcmncr_val |= SNAND_E;
	else
		flcmncr_val &= ~SNAND_E;

	/* default FLCMDCR val */
	flcmdcr_val = DOCMD1_E | DOADR_E;

	/* Set for FLCMDCR */
	switch (cmd) {
	case NAND_CMD_ERASE1:
		addr_len_bytes = flctl->erase_ADRCNT;
		flcmdcr_val |= DOCMD2_E;
		break;
	case NAND_CMD_READ0:
	case NAND_CMD_READOOB:
		addr_len_bytes = flctl->rw_ADRCNT;
		flcmdcr_val |= CDSRC_E;
		break;
	case NAND_CMD_SEQIN:
		/* This case is that cmd is READ0 or READ1 or READ00 */
		flcmdcr_val &= ~DOADR_E;	/* ONLY execute 1st cmd */
		break;
	case NAND_CMD_PAGEPROG:
		addr_len_bytes = flctl->rw_ADRCNT;
		flcmdcr_val |= DOCMD2_E | CDSRC_E | SELRW;
		break;
	case NAND_CMD_READID:
		flcmncr_val &= ~SNAND_E;
		addr_len_bytes = ADRCNT_1;
		break;
	case NAND_CMD_STATUS:
	case NAND_CMD_RESET:
		flcmncr_val &= ~SNAND_E;
		flcmdcr_val &= ~(DOADR_E | DOSR_E);
		break;
	default:
		break;
	}

	/* Set address bytes parameter */
	flcmdcr_val |= addr_len_bytes;

	/* Now actually write */
	writel(flcmncr_val, FLCMNCR(flctl));
	writel(flcmdcr_val, FLCMDCR(flctl));
	writel(flcmcdr_val, FLCMCDR(flctl));
}