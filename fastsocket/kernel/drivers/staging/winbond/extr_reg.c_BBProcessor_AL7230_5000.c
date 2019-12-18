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
struct wb35_reg {int BB0C; int BB2C; int BB3C; int BB50; int BB54; int BB58; } ;
struct hw_data {struct wb35_reg reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_INCREMENT ; 
 int /*<<< orphan*/  Wb35Reg_BurstWrite (struct hw_data*,int,int*,int,int /*<<< orphan*/ ) ; 

void BBProcessor_AL7230_5000(  struct hw_data * pHwData)
{
	struct wb35_reg *reg = &pHwData->reg;
	u32	pltmp[12];

	pltmp[0] = 0x16AA6678; // 0x1000 AGC_Ctrl1
	pltmp[1] = 0x9AFFA0B2; // 0x1004 AGC_Ctrl2
	pltmp[2] = 0x55D00A04; // 0x1008 AGC_Ctrl3
	pltmp[3] = 0xEFFF233E; // 0x100c AGC_Ctrl4
	reg->BB0C = 0xEFFF233E;
	pltmp[4] = 0x0FacDCC5; // 0x1010 AGC_Ctrl5 // 20050927 0x0FacDCB7
	pltmp[5] = 0x00CAA333; // 0x1014 AGC_Ctrl6
	pltmp[6] = 0xF2432111; // 0x1018 AGC_Ctrl7
	pltmp[7] = 0x0FA3F0ED; // 0x101c AGC_Ctrl8
	pltmp[8] = 0x05C43440; // 0x1020 AGC_Ctrl9
	pltmp[9] = 0x00002A79; // 0x1024 AGC_Ctrl10
	pltmp[10] = 0x40000528; // 20050927 0x40000228
	pltmp[11] = 0x232FDF30;// 0x102c A_ACQ_Ctrl
	reg->BB2C = 0x232FDF30;
	Wb35Reg_BurstWrite( pHwData, 0x1000, pltmp, 12, AUTO_INCREMENT );

	pltmp[0] = 0x80002C7C; // 0x1030 B_ACQ_Ctrl
	pltmp[1] = 0x00C0D6C5; // 0x1034 A_TXRX_Ctrl
	pltmp[2] = 0x5B2C8769; // 0x1038 B_TXRX_Ctrl
	pltmp[3] = 0x00000000; // 0x103c 11a TX LS filter
	reg->BB3C = 0x00000000;
	pltmp[4] = 0x00003F29; // 0x1040 11a TX LS filter
	pltmp[5] = 0x0EFEFBFE; // 0x1044 11a TX LS filter
	pltmp[6] = 0x00332C1B; // 0x1048 11b TX RC filter
	pltmp[7] = 0x0A00FEFF; // 0x104c 11b TX RC filter
	pltmp[8] = 0x2B107208; // 0x1050 MODE_Ctrl
	reg->BB50 = 0x2B107208;
	pltmp[9] = 0; // 0x1054
	reg->BB54 = 0x00000000;
	pltmp[10] = 0x52524242; // 0x1058 IQ_Alpha
	reg->BB58 = 0x52524242;
	pltmp[11] = 0xAA0AC000; // 0x105c DC_Cancel
	Wb35Reg_BurstWrite( pHwData, 0x1030, pltmp, 12, AUTO_INCREMENT );

}