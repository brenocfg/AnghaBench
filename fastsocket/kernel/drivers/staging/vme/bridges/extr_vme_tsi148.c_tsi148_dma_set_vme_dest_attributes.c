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
typedef  int vme_width_t ;
typedef  int vme_cycle_t ;
typedef  int vme_address_t ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_2eSSTM_160 ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_2eSSTM_267 ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_2eSSTM_320 ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_AMODE_A16 ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_AMODE_A24 ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_AMODE_A32 ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_AMODE_A64 ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_AMODE_CRCSR ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_AMODE_USER1 ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_AMODE_USER2 ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_AMODE_USER3 ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_AMODE_USER4 ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_DBW_16 ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_DBW_32 ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_PGM ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_SUP ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_TM_2eSST ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_TM_2eSSTB ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_TM_2eVME ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_TM_BLT ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_TM_MBLT ; 
 int /*<<< orphan*/  TSI148_LCSR_DDAT_TM_SCT ; 
 int VME_2eSST ; 
#define  VME_2eSST160 141 
#define  VME_2eSST267 140 
#define  VME_2eSST320 139 
 int VME_2eSSTB ; 
 int VME_2eVME ; 
#define  VME_A16 138 
#define  VME_A24 137 
#define  VME_A32 136 
#define  VME_A64 135 
 int VME_BLT ; 
#define  VME_CRCSR 134 
#define  VME_D16 133 
#define  VME_D32 132 
 int VME_MBLT ; 
 int VME_PROG ; 
 int VME_SCT ; 
 int VME_SUPER ; 
#define  VME_USER1 131 
#define  VME_USER2 130 
#define  VME_USER3 129 
#define  VME_USER4 128 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int tsi148_dma_set_vme_dest_attributes(u32 *attr, vme_address_t aspace,
	vme_cycle_t cycle, vme_width_t dwidth)
{
	/* Setup 2eSST speeds */
	switch (cycle & (VME_2eSST160 | VME_2eSST267 | VME_2eSST320)) {
	case VME_2eSST160:
		*attr |= TSI148_LCSR_DDAT_2eSSTM_160;
		break;
	case VME_2eSST267:
		*attr |= TSI148_LCSR_DDAT_2eSSTM_267;
		break;
	case VME_2eSST320:
		*attr |= TSI148_LCSR_DDAT_2eSSTM_320;
		break;
	}

	/* Setup cycle types */
	if (cycle & VME_SCT) {
		*attr |= TSI148_LCSR_DDAT_TM_SCT;
	}
	if (cycle & VME_BLT) {
		*attr |= TSI148_LCSR_DDAT_TM_BLT;
	}
	if (cycle & VME_MBLT) {
		*attr |= TSI148_LCSR_DDAT_TM_MBLT;
	}
	if (cycle & VME_2eVME) {
		*attr |= TSI148_LCSR_DDAT_TM_2eVME;
	}
	if (cycle & VME_2eSST) {
		*attr |= TSI148_LCSR_DDAT_TM_2eSST;
	}
	if (cycle & VME_2eSSTB) {
		printk("Currently not setting Broadcast Select Registers\n");
		*attr |= TSI148_LCSR_DDAT_TM_2eSSTB;
	}

	/* Setup data width */
	switch (dwidth) {
	case VME_D16:
		*attr |= TSI148_LCSR_DDAT_DBW_16;
		break;
	case VME_D32:
		*attr |= TSI148_LCSR_DDAT_DBW_32;
		break;
	default:
		printk("Invalid data width\n");
		return -EINVAL;
	}

	/* Setup address space */
	switch (aspace) {
	case VME_A16:
		*attr |= TSI148_LCSR_DDAT_AMODE_A16;
		break;
	case VME_A24:
		*attr |= TSI148_LCSR_DDAT_AMODE_A24;
		break;
	case VME_A32:
		*attr |= TSI148_LCSR_DDAT_AMODE_A32;
		break;
	case VME_A64:
		*attr |= TSI148_LCSR_DDAT_AMODE_A64;
		break;
	case VME_CRCSR:
		*attr |= TSI148_LCSR_DDAT_AMODE_CRCSR;
		break;
	case VME_USER1:
		*attr |= TSI148_LCSR_DDAT_AMODE_USER1;
		break;
	case VME_USER2:
		*attr |= TSI148_LCSR_DDAT_AMODE_USER2;
		break;
	case VME_USER3:
		*attr |= TSI148_LCSR_DDAT_AMODE_USER3;
		break;
	case VME_USER4:
		*attr |= TSI148_LCSR_DDAT_AMODE_USER4;
		break;
	default:
		printk("Invalid address space\n");
		return -EINVAL;
		break;
	}

	if (cycle & VME_SUPER)
		*attr |= TSI148_LCSR_DDAT_SUP;
	if (cycle & VME_PROG)
		*attr |= TSI148_LCSR_DDAT_PGM;

	return 0;
}