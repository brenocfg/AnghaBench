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
typedef  void* u8 ;
typedef  size_t u32 ;
struct wb35_reg {int BB0C; int BB2C; int BB30; int BB3C; int BB50; int BB54; int BB58; int* SQ3_filter; void** LNAValue; void* BB4C; void* BB48; } ;
struct hw_data {int phy_type; size_t BB3c_cal; size_t BB54_cal; struct wb35_reg reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_INCREMENT ; 
 void* BB48_DEFAULT_AL2230_11G ; 
 void* BB48_DEFAULT_WB242_11G ; 
 void* BB4C_DEFAULT_AL2230_11G ; 
 void* BB4C_DEFAULT_WB242_11G ; 
 int /*<<< orphan*/  BBProcessor_AL7230_2400 (struct hw_data*) ; 
 size_t MAX_SQ3_FILTER_SIZE ; 
#define  RF_AIROHA_2230 137 
#define  RF_AIROHA_2230S 136 
#define  RF_AIROHA_7230 135 
#define  RF_MAXIM_2825 134 
#define  RF_MAXIM_2827 133 
#define  RF_MAXIM_2828 132 
#define  RF_MAXIM_2829 131 
#define  RF_MAXIM_V1 130 
#define  RF_WB_242 129 
#define  RF_WB_242_1 128 
 int /*<<< orphan*/  Wb35Reg_BurstWrite (struct hw_data*,int,size_t*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Wb35Reg_Write (struct hw_data*,int,int) ; 

void
BBProcessor_initial(  struct hw_data * pHwData )
{
	struct wb35_reg *reg = &pHwData->reg;
	u32	i, pltmp[12];

    switch( pHwData->phy_type )
    {
		case RF_MAXIM_V1: // Initializng the Winbond 2nd BB(with Phy board (v1) + Maxim 331)

			pltmp[0] = 0x16F47E77; // 0x1000 AGC_Ctrl1
			pltmp[1] = 0x9AFFAEA4; // 0x1004 AGC_Ctrl2
			pltmp[2] = 0x55D00A04; // 0x1008 AGC_Ctrl3
			pltmp[3] = 0xEFFF1A34; // 0x100c AGC_Ctrl4
			reg->BB0C = 0xEFFF1A34;
			pltmp[4] = 0x0FABE0B7; // 0x1010 AGC_Ctrl5
			pltmp[5] = 0x00CAA332; // 0x1014 AGC_Ctrl6
			pltmp[6] = 0xF6632111; // 0x1018 AGC_Ctrl7
			pltmp[7] = 0x0FA3F0ED; // 0x101c AGC_Ctrl8
			pltmp[8] = 0x04CC3640; // 0x1020 AGC_Ctrl9
			pltmp[9] = 0x00002A79; // 0x1024 AGC_Ctrl10
			pltmp[10] = (pHwData->phy_type==3) ? 0x40000a28 : 0x40000228; // 0x1028 MAXIM_331(b31=0) + WBRF_V1(b11=1) : MAXIM_331(b31=0) + WBRF_V2(b11=0)
			pltmp[11] = 0x232FDF30; // 0x102c A_ACQ_Ctrl
			reg->BB2C = 0x232FDF30; //Modify for 33's 1.0.95.xxx version, antenna 1
			Wb35Reg_BurstWrite( pHwData, 0x1000, pltmp, 12, AUTO_INCREMENT );

			pltmp[0] = 0x00002C54; // 0x1030 B_ACQ_Ctrl
			reg->BB30 = 0x00002C54;
			pltmp[1] = 0x00C0D6C5; // 0x1034 A_TXRX_Ctrl
			pltmp[2] = 0x5B6C8769; // 0x1038 B_TXRX_Ctrl
			pltmp[3] = 0x00000000; // 0x103c 11a TX LS filter
			reg->BB3C = 0x00000000;
			pltmp[4] = 0x00003F29; // 0x1040 11a TX LS filter
			pltmp[5] = 0x0EFEFBFE; // 0x1044 11a TX LS filter
			pltmp[6] = 0x00453B24; // 0x1048 11b TX RC filter
			pltmp[7] = 0x0E00FEFF; // 0x104c 11b TX RC filter
			pltmp[8] = 0x27106208; // 0x1050 MODE_Ctrl
			reg->BB50 = 0x27106208;
			pltmp[9] = 0; // 0x1054
			reg->BB54 = 0x00000000;
			pltmp[10] = 0x64646464; // 0x1058 IQ_Alpha
			reg->BB58 = 0x64646464;
			pltmp[11] = 0xAA0AC000; // 0x105c DC_Cancel
			Wb35Reg_BurstWrite( pHwData, 0x1030, pltmp, 12, AUTO_INCREMENT );

			Wb35Reg_Write( pHwData, 0x1070, 0x00000045 );
			break;

		//------------------------------------------------------------------
		//[20040722 WK]
		//Only for baseband version 2
//		case RF_MAXIM_317:
		case RF_MAXIM_2825:
		case RF_MAXIM_2827:
		case RF_MAXIM_2828:

			pltmp[0] = 0x16b47e77; // 0x1000 AGC_Ctrl1
			pltmp[1] = 0x9affaea4; // 0x1004 AGC_Ctrl2
			pltmp[2] = 0x55d00a04; // 0x1008 AGC_Ctrl3
			pltmp[3] = 0xefff1a34; // 0x100c AGC_Ctrl4
			reg->BB0C = 0xefff1a34;
			pltmp[4] = 0x0fabe0b7; // 0x1010 AGC_Ctrl5
			pltmp[5] = 0x00caa332; // 0x1014 AGC_Ctrl6
			pltmp[6] = 0xf6632111; // 0x1018 AGC_Ctrl7
			pltmp[7] = 0x0FA3F0ED; // 0x101c AGC_Ctrl8
			pltmp[8] = 0x04CC3640; // 0x1020 AGC_Ctrl9
			pltmp[9] = 0x00002A79; // 0x1024 AGC_Ctrl10
			pltmp[10] = 0x40000528; // 0x40000128; Modify for 33's 1.0.95
			pltmp[11] = 0x232fdf30; // 0x102c A_ACQ_Ctrl
			reg->BB2C = 0x232fdf30; //Modify for 33's 1.0.95.xxx version, antenna 1
			Wb35Reg_BurstWrite( pHwData, 0x1000, pltmp, 12, AUTO_INCREMENT );

			pltmp[0] = 0x00002C54; // 0x1030 B_ACQ_Ctrl
			reg->BB30 = 0x00002C54;
			pltmp[1] = 0x00C0D6C5; // 0x1034 A_TXRX_Ctrl
			pltmp[2] = 0x5B6C8769; // 0x1038 B_TXRX_Ctrl
			pltmp[3] = 0x00000000; // 0x103c 11a TX LS filter
			reg->BB3C = 0x00000000;
			pltmp[4] = 0x00003F29; // 0x1040 11a TX LS filter
			pltmp[5] = 0x0EFEFBFE; // 0x1044 11a TX LS filter
			pltmp[6] = 0x00453B24; // 0x1048 11b TX RC filter
			pltmp[7] = 0x0D00FDFF; // 0x104c 11b TX RC filter
			pltmp[8] = 0x27106208; // 0x1050 MODE_Ctrl
			reg->BB50 = 0x27106208;
			pltmp[9] = 0; // 0x1054
			reg->BB54 = 0x00000000;
			pltmp[10] = 0x64646464; // 0x1058 IQ_Alpha
			reg->BB58 = 0x64646464;
			pltmp[11] = 0xAA28C000; // 0x105c DC_Cancel
			Wb35Reg_BurstWrite( pHwData, 0x1030, pltmp, 12, AUTO_INCREMENT );

			Wb35Reg_Write( pHwData, 0x1070, 0x00000045 );
			break;

		case RF_MAXIM_2829:

			pltmp[0] = 0x16b47e77; // 0x1000 AGC_Ctrl1
			pltmp[1] = 0x9affaea4; // 0x1004 AGC_Ctrl2
			pltmp[2] = 0x55d00a04; // 0x1008 AGC_Ctrl3
			pltmp[3] = 0xf4ff1632; // 0xefff1a34; // 0x100c AGC_Ctrl4 Modify for 33's 1.0.95
			reg->BB0C = 0xf4ff1632; // 0xefff1a34; Modify for 33's 1.0.95
			pltmp[4] = 0x0fabe0b7; // 0x1010 AGC_Ctrl5
			pltmp[5] = 0x00caa332; // 0x1014 AGC_Ctrl6
			pltmp[6] = 0xf8632112; // 0xf6632111; // 0x1018 AGC_Ctrl7 Modify for 33's 1.0.95
			pltmp[7] = 0x0FA3F0ED; // 0x101c AGC_Ctrl8
			pltmp[8] = 0x04CC3640; // 0x1020 AGC_Ctrl9
			pltmp[9] = 0x00002A79; // 0x1024 AGC_Ctrl10
			pltmp[10] = 0x40000528; // 0x40000128; modify for 33's 1.0.95
			pltmp[11] = 0x232fdf30; // 0x102c A_ACQ_Ctrl
			reg->BB2C = 0x232fdf30; //Modify for 33's 1.0.95.xxx version, antenna 1
			Wb35Reg_BurstWrite( pHwData, 0x1000, pltmp, 12, AUTO_INCREMENT );

			pltmp[0] = 0x00002C54; // 0x1030 B_ACQ_Ctrl
			reg->BB30 = 0x00002C54;
			pltmp[1] = 0x00C0D6C5; // 0x1034 A_TXRX_Ctrl
			pltmp[2] = 0x5b2c8769; // 0x5B6C8769; // 0x1038 B_TXRX_Ctrl Modify for 33's 1.0.95
			pltmp[3] = 0x00000000; // 0x103c 11a TX LS filter
			reg->BB3C = 0x00000000;
			pltmp[4] = 0x00003F29; // 0x1040 11a TX LS filter
			pltmp[5] = 0x0EFEFBFE; // 0x1044 11a TX LS filter
			pltmp[6] = 0x002c2617; // 0x00453B24; // 0x1048 11b TX RC filter Modify for 33's 1.0.95
			pltmp[7] = 0x0800feff; // 0x0D00FDFF; // 0x104c 11b TX RC filter Modify for 33's 1.0.95
			pltmp[8] = 0x27106208; // 0x1050 MODE_Ctrl
			reg->BB50 = 0x27106208;
			pltmp[9] = 0; // 0x1054
			reg->BB54 = 0x00000000;
			pltmp[10] = 0x64644a4a; // 0x64646464; // 0x1058 IQ_Alpha Modify for 33's 1.0.95
			reg->BB58 = 0x64646464;
			pltmp[11] = 0xAA28C000; // 0x105c DC_Cancel
			Wb35Reg_BurstWrite( pHwData, 0x1030, pltmp, 12, AUTO_INCREMENT );

			Wb35Reg_Write( pHwData, 0x1070, 0x00000045 );
			break;

		case RF_AIROHA_2230:

			pltmp[0] = 0X16764A77; // 0x1000 AGC_Ctrl1		//0x16765A77
			pltmp[1] = 0x9affafb2; // 0x1004 AGC_Ctrl2
			pltmp[2] = 0x55d00a04; // 0x1008 AGC_Ctrl3
			pltmp[3] = 0xFFFd203c; // 0xFFFb203a; // 0x100c AGC_Ctrl4 Modify for 33's 1.0.95.xxx version
			reg->BB0C = 0xFFFd203c;
			pltmp[4] = 0X0FBFDCc5; // 0X0FBFDCA0; // 0x1010 AGC_Ctrl5 //0x0FB2E0B7 Modify for 33's 1.0.95.xxx version
			pltmp[5] = 0x00caa332; // 0x00caa333; // 0x1014 AGC_Ctrl6 Modify for 33's 1.0.95.xxx version
			pltmp[6] = 0XF6632111; // 0XF1632112; // 0x1018 AGC_Ctrl7		//0xf6632112 Modify for 33's 1.0.95.xxx version
			pltmp[7] = 0x0FA3F0ED; // 0x101c AGC_Ctrl8
			pltmp[8] = 0x04C43640; // 0x1020 AGC_Ctrl9
			pltmp[9] = 0x00002A79; // 0x1024 AGC_Ctrl10
			pltmp[10] = 0X40000528;							//0x40000228
			pltmp[11] = 0x232dfF30; // 0x232A9F30; // 0x102c A_ACQ_Ctrl	//0x232a9730
			reg->BB2C = 0x232dfF30; //Modify for 33's 1.0.95.xxx version, antenna 1
			Wb35Reg_BurstWrite( pHwData, 0x1000, pltmp, 12, AUTO_INCREMENT );

			pltmp[0] = 0x00002C54; // 0x1030 B_ACQ_Ctrl
			reg->BB30 = 0x00002C54;
			pltmp[1] = 0x00C0D6C5; // 0x1034 A_TXRX_Ctrl
			pltmp[2] = 0x5B2C8769; // 0x1038 B_TXRX_Ctrl	//0x5B6C8769
			pltmp[3] = 0x00000000; // 0x103c 11a TX LS filter
			reg->BB3C = 0x00000000;
			pltmp[4] = 0x00003F29; // 0x1040 11a TX LS filter
			pltmp[5] = 0x0EFEFBFE; // 0x1044 11a TX LS filter
			pltmp[6] = BB48_DEFAULT_AL2230_11G; // 0x1048 11b TX RC filter 20060613.2
			reg->BB48 = BB48_DEFAULT_AL2230_11G; // 20051221 ch14 20060613.2
			pltmp[7] = BB4C_DEFAULT_AL2230_11G; // 0x104c 11b TX RC filter 20060613.2
			reg->BB4C = BB4C_DEFAULT_AL2230_11G; // 20060613.1 20060613.2
			pltmp[8] = 0x27106200; // 0x1050 MODE_Ctrl
			reg->BB50 = 0x27106200;
			pltmp[9] = 0; // 0x1054
			reg->BB54 = 0x00000000;
			pltmp[10] = 0x52524242; // 0x1058 IQ_Alpha
			reg->BB58 = 0x52524242;
			pltmp[11] = 0xAA0AC000; // 0x105c DC_Cancel
			Wb35Reg_BurstWrite( pHwData, 0x1030, pltmp, 12, AUTO_INCREMENT );

			Wb35Reg_Write( pHwData, 0x1070, 0x00000045 );
			break;

		case RF_AIROHA_2230S: // 20060420 Add this

			pltmp[0] = 0X16764A77; // 0x1000 AGC_Ctrl1		//0x16765A77
			pltmp[1] = 0x9affafb2; // 0x1004 AGC_Ctrl2
			pltmp[2] = 0x55d00a04; // 0x1008 AGC_Ctrl3
			pltmp[3] = 0xFFFd203c; // 0xFFFb203a; // 0x100c AGC_Ctrl4 Modify for 33's 1.0.95.xxx version
			reg->BB0C = 0xFFFd203c;
			pltmp[4] = 0X0FBFDCc5; // 0X0FBFDCA0; // 0x1010 AGC_Ctrl5 //0x0FB2E0B7 Modify for 33's 1.0.95.xxx version
			pltmp[5] = 0x00caa332; // 0x00caa333; // 0x1014 AGC_Ctrl6 Modify for 33's 1.0.95.xxx version
			pltmp[6] = 0XF6632111; // 0XF1632112; // 0x1018 AGC_Ctrl7		//0xf6632112 Modify for 33's 1.0.95.xxx version
			pltmp[7] = 0x0FA3F0ED; // 0x101c AGC_Ctrl8
			pltmp[8] = 0x04C43640; // 0x1020 AGC_Ctrl9
			pltmp[9] = 0x00002A79; // 0x1024 AGC_Ctrl10
			pltmp[10] = 0X40000528;							//0x40000228
			pltmp[11] = 0x232dfF30; // 0x232A9F30; // 0x102c A_ACQ_Ctrl	//0x232a9730
			reg->BB2C = 0x232dfF30; //Modify for 33's 1.0.95.xxx version, antenna 1
			Wb35Reg_BurstWrite( pHwData, 0x1000, pltmp, 12, AUTO_INCREMENT );

			pltmp[0] = 0x00002C54; // 0x1030 B_ACQ_Ctrl
			reg->BB30 = 0x00002C54;
			pltmp[1] = 0x00C0D6C5; // 0x1034 A_TXRX_Ctrl
			pltmp[2] = 0x5B2C8769; // 0x1038 B_TXRX_Ctrl	//0x5B6C8769
			pltmp[3] = 0x00000000; // 0x103c 11a TX LS filter
			reg->BB3C = 0x00000000;
			pltmp[4] = 0x00003F29; // 0x1040 11a TX LS filter
			pltmp[5] = 0x0EFEFBFE; // 0x1044 11a TX LS filter
			pltmp[6] = BB48_DEFAULT_AL2230_11G; // 0x1048 11b TX RC filter 20060613.2
			reg->BB48 = BB48_DEFAULT_AL2230_11G; // 20051221 ch14 20060613.2
			pltmp[7] = BB4C_DEFAULT_AL2230_11G; // 0x104c 11b TX RC filter 20060613.2
			reg->BB4C = BB4C_DEFAULT_AL2230_11G; // 20060613.1
			pltmp[8] = 0x27106200; // 0x1050 MODE_Ctrl
			reg->BB50 = 0x27106200;
			pltmp[9] = 0; // 0x1054
			reg->BB54 = 0x00000000;
			pltmp[10] = 0x52523232; // 20060419 0x52524242; // 0x1058 IQ_Alpha
			reg->BB58 = 0x52523232; // 20060419 0x52524242;
			pltmp[11] = 0xAA0AC000; // 0x105c DC_Cancel
			Wb35Reg_BurstWrite( pHwData, 0x1030, pltmp, 12, AUTO_INCREMENT );

			Wb35Reg_Write( pHwData, 0x1070, 0x00000045 );
			break;

		case RF_AIROHA_7230:
/*
			pltmp[0] = 0x16a84a77; // 0x1000 AGC_Ctrl1
			pltmp[1] = 0x9affafb2; // 0x1004 AGC_Ctrl2
			pltmp[2] = 0x55d00a04; // 0x1008 AGC_Ctrl3
			pltmp[3] = 0xFFFb203a; // 0x100c AGC_Ctrl4
			reg->BB0c = 0xFFFb203a;
			pltmp[4] = 0x0FBFDCB7; // 0x1010 AGC_Ctrl5
			pltmp[5] = 0x00caa333; // 0x1014 AGC_Ctrl6
			pltmp[6] = 0xf6632112; // 0x1018 AGC_Ctrl7
			pltmp[7] = 0x0FA3F0ED; // 0x101c AGC_Ctrl8
			pltmp[8] = 0x04C43640; // 0x1020 AGC_Ctrl9
			pltmp[9] = 0x00002A79; // 0x1024 AGC_Ctrl10
			pltmp[10] = 0x40000228;
			pltmp[11] = 0x232A9F30;// 0x102c A_ACQ_Ctrl
			reg->BB2c = 0x232A9F30;
			Wb35Reg_BurstWrite( pHwData, 0x1000, pltmp, 12, AUTO_INCREMENT );

			pltmp[0] = 0x00002C54; // 0x1030 B_ACQ_Ctrl
			reg->BB30 = 0x00002C54;
			pltmp[1] = 0x00C0D6C5; // 0x1034 A_TXRX_Ctrl
			pltmp[2] = 0x5B2C8769; // 0x1038 B_TXRX_Ctrl
			pltmp[3] = 0x00000000; // 0x103c 11a TX LS filter
			reg->BB3c = 0x00000000;
			pltmp[4] = 0x00003F29; // 0x1040 11a TX LS filter
			pltmp[5] = 0x0EFEFBFE; // 0x1044 11a TX LS filter
			pltmp[6] = 0x00453B24; // 0x1048 11b TX RC filter
			pltmp[7] = 0x0E00FEFF; // 0x104c 11b TX RC filter
			pltmp[8] = 0x27106200; // 0x1050 MODE_Ctrl
			reg->BB50 = 0x27106200;
			pltmp[9] = 0; // 0x1054
			reg->BB54 = 0x00000000;
			pltmp[10] = 0x64645252; // 0x1058 IQ_Alpha
			reg->BB58 = 0x64645252;
			pltmp[11] = 0xAA0AC000; // 0x105c DC_Cancel
			Wb35Reg_BurstWrite( pHwData, 0x1030, pltmp, 12, AUTO_INCREMENT );
*/
			BBProcessor_AL7230_2400( pHwData );

			Wb35Reg_Write( pHwData, 0x1070, 0x00000045 );
			break;

		case RF_WB_242:
		case RF_WB_242_1: // 20060619.5 Add

			pltmp[0] = 0x16A8525D; // 0x1000 AGC_Ctrl1
			pltmp[1] = 0x9AFF9ABA; // 0x1004 AGC_Ctrl2
			pltmp[2] = 0x55D00A04; // 0x1008 AGC_Ctrl3
			pltmp[3] = 0xEEE91C32; // 0x100c AGC_Ctrl4
			reg->BB0C = 0xEEE91C32;
			pltmp[4] = 0x0FACDCC5; // 0x1010 AGC_Ctrl5
			pltmp[5] = 0x000AA344; // 0x1014 AGC_Ctrl6
			pltmp[6] = 0x22222221; // 0x1018 AGC_Ctrl7
			pltmp[7] = 0x0FA3F0ED; // 0x101c AGC_Ctrl8
			pltmp[8] = 0x04CC3440; // 20051018 0x03CB3440; // 0x1020 AGC_Ctrl9 20051014 0x03C33440
			pltmp[9] = 0xA9002A79; // 0x1024 AGC_Ctrl10
			pltmp[10] = 0x40000528; // 0x1028
			pltmp[11] = 0x23457F30; // 0x102c A_ACQ_Ctrl
			reg->BB2C = 0x23457F30;
			Wb35Reg_BurstWrite( pHwData, 0x1000, pltmp, 12, AUTO_INCREMENT );

			pltmp[0] = 0x00002C54; // 0x1030 B_ACQ_Ctrl
			reg->BB30 = 0x00002C54;
			pltmp[1] = 0x00C0D6C5; // 0x1034 A_TXRX_Ctrl
			pltmp[2] = 0x5B2C8769; // 0x1038 B_TXRX_Ctrl
			pltmp[3] = pHwData->BB3c_cal; // 0x103c 11a TX LS filter
			reg->BB3C = pHwData->BB3c_cal;
			pltmp[4] = 0x00003F29; // 0x1040 11a TX LS filter
			pltmp[5] = 0x0EFEFBFE; // 0x1044 11a TX LS filter
			pltmp[6] = BB48_DEFAULT_WB242_11G; // 0x1048 11b TX RC filter 20060613.2
			reg->BB48 = BB48_DEFAULT_WB242_11G; // 20060613.1 20060613.2
			pltmp[7] = BB4C_DEFAULT_WB242_11G; // 0x104c 11b TX RC filter 20060613.2
			reg->BB4C = BB4C_DEFAULT_WB242_11G; // 20060613.1 20060613.2
			pltmp[8] = 0x27106208; // 0x1050 MODE_Ctrl
			reg->BB50 = 0x27106208;
			pltmp[9] = pHwData->BB54_cal; // 0x1054
			reg->BB54 = pHwData->BB54_cal;
			pltmp[10] = 0x52523131; // 0x1058 IQ_Alpha
			reg->BB58 = 0x52523131;
			pltmp[11] = 0xAA0AC000; // 20060825 0xAA2AC000; // 0x105c DC_Cancel
			Wb35Reg_BurstWrite( pHwData, 0x1030, pltmp, 12, AUTO_INCREMENT );

			Wb35Reg_Write( pHwData, 0x1070, 0x00000045 );
			break;
    }

	// Fill the LNA table
	reg->LNAValue[0] = (u8)(reg->BB0C & 0xff);
	reg->LNAValue[1] = 0;
	reg->LNAValue[2] = (u8)((reg->BB0C & 0xff00)>>8);
	reg->LNAValue[3] = 0;

	// Fill SQ3 table
	for( i=0; i<MAX_SQ3_FILTER_SIZE; i++ )
		reg->SQ3_filter[i] = 0x2f; // half of Bit 0 ~ 6
}