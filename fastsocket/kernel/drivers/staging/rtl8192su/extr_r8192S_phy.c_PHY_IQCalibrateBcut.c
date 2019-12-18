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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BIT27 ; 
 int BIT28 ; 
 int BIT30 ; 
 int BIT31 ; 
 int /*<<< orphan*/  BIT8 ; 
 int /*<<< orphan*/  COMP_INIT ; 
 size_t RF90_PATH_A ; 
 size_t RF90_PATH_C ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int rFPGA0_XA_HSSIParameter1 ; 
 int rtl8192_QueryBBReg (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

extern void PHY_IQCalibrateBcut(struct net_device* dev)
{
	//struct r8192_priv 	*priv = ieee80211_priv(dev);
	//PMGNT_INFO		pMgntInfo = &pAdapter->MgntInfo;
	u32				i, reg;
	u32				old_value;
	long				X, Y, TX0[4];
	u32				TXA[4];
	u32				calibrate_set[13] = {0};
	u32				load_value[13];
	u8				RfPiEnable=0;

	// 0. Check QFN68 or 64 92S (Read from EEPROM/EFUSE)

	//
	// 1. Save e70~ee0 register setting, and load calibration setting
	//
	/*
	0xee0[31:0]=0x3fed92fb;
	0xedc[31:0] =0x3fed92fb;
	0xe70[31:0] =0x3fed92fb;
	0xe74[31:0] =0x3fed92fb;
	0xe78[31:0] =0x3fed92fb;
	0xe7c[31:0]= 0x3fed92fb;
	0xe80[31:0]= 0x3fed92fb;
	0xe84[31:0]= 0x3fed92fb;
	0xe88[31:0]= 0x3fed92fb;
	0xe8c[31:0]= 0x3fed92fb;
	0xed0[31:0]= 0x3fed92fb;
	0xed4[31:0]= 0x3fed92fb;
	0xed8[31:0]= 0x3fed92fb;
	*/
	calibrate_set [0] = 0xee0;
	calibrate_set [1] = 0xedc;
	calibrate_set [2] = 0xe70;
	calibrate_set [3] = 0xe74;
	calibrate_set [4] = 0xe78;
	calibrate_set [5] = 0xe7c;
	calibrate_set [6] = 0xe80;
	calibrate_set [7] = 0xe84;
	calibrate_set [8] = 0xe88;
	calibrate_set [9] = 0xe8c;
	calibrate_set [10] = 0xed0;
	calibrate_set [11] = 0xed4;
	calibrate_set [12] = 0xed8;
	//RT_TRACE(COMP_INIT, DBG_LOUD, ("Save e70~ee0 register setting\n"));
	for (i = 0; i < 13; i++)
	{
		load_value[i] = rtl8192_QueryBBReg(dev, calibrate_set[i], bMaskDWord);
		rtl8192_setBBreg(dev, calibrate_set[i], bMaskDWord, 0x3fed92fb);

	}

	RfPiEnable = (u8)rtl8192_QueryBBReg(dev, rFPGA0_XA_HSSIParameter1, BIT8);

	//
	// 2. QFN 68
	//
	// For 1T2R IQK only now !!!
	for (i = 0; i < 10; i++)
	{
		RT_TRACE(COMP_INIT, "IQK -%d\n", i);
		//BB switch to PI mode. If default is PI mode, ignoring 2 commands below.
		if (!RfPiEnable)	//if original is SI mode, then switch to PI mode.
		{
			//DbgPrint("IQK Switch to PI mode\n");
			rtl8192_setBBreg(dev, 0x820, bMaskDWord, 0x01000100);
			rtl8192_setBBreg(dev, 0x828, bMaskDWord, 0x01000100);
		}

		// IQK
		// 2. IQ calibration & LO leakage calibration
		rtl8192_setBBreg(dev, 0xc04, bMaskDWord, 0x00a05430);
		udelay(5);
		rtl8192_setBBreg(dev, 0xc08, bMaskDWord, 0x000800e4);
		udelay(5);
		rtl8192_setBBreg(dev, 0xe28, bMaskDWord, 0x80800000);
		udelay(5);
		//path-A IQ K and LO K gain setting
		rtl8192_setBBreg(dev, 0xe40, bMaskDWord, 0x02140102);
		udelay(5);
		rtl8192_setBBreg(dev, 0xe44, bMaskDWord, 0x681604c2);
		udelay(5);
		//set LO calibration
		rtl8192_setBBreg(dev, 0xe4c, bMaskDWord, 0x000028d1);
		udelay(5);
		//path-B IQ K and LO K gain setting
		rtl8192_setBBreg(dev, 0xe60, bMaskDWord, 0x02140102);
		udelay(5);
		rtl8192_setBBreg(dev, 0xe64, bMaskDWord, 0x28160d05);
		udelay(5);
		//K idac_I & IQ
		rtl8192_setBBreg(dev, 0xe48, bMaskDWord, 0xfb000000);
		udelay(5);
		rtl8192_setBBreg(dev, 0xe48, bMaskDWord, 0xf8000000);
		udelay(5);

		// delay 2ms
		udelay(2000);

		//idac_Q setting
		rtl8192_setBBreg(dev, 0xe6c, bMaskDWord, 0x020028d1);
		udelay(5);
		//K idac_Q & IQ
		rtl8192_setBBreg(dev, 0xe48, bMaskDWord, 0xfb000000);
		udelay(5);
		rtl8192_setBBreg(dev, 0xe48, bMaskDWord, 0xf8000000);

		// delay 2ms
		udelay(2000);

		rtl8192_setBBreg(dev, 0xc04, bMaskDWord, 0x00a05433);
		udelay(5);
		rtl8192_setBBreg(dev, 0xc08, bMaskDWord, 0x000000e4);
		udelay(5);
		rtl8192_setBBreg(dev, 0xe28, bMaskDWord, 0x0);

		if (!RfPiEnable)	//if original is SI mode, then switch to PI mode.
		{
			//DbgPrint("IQK Switch back to SI mode\n");
			rtl8192_setBBreg(dev, 0x820, bMaskDWord, 0x01000000);
			rtl8192_setBBreg(dev, 0x828, bMaskDWord, 0x01000000);
		}


		reg = rtl8192_QueryBBReg(dev, 0xeac, bMaskDWord);

		// 3.	check fail bit, and fill BB IQ matrix
		// Readback IQK value and rewrite
		if (!(reg&(BIT27|BIT28|BIT30|BIT31)))
		{
			old_value = (rtl8192_QueryBBReg(dev, 0xc80, bMaskDWord) & 0x3FF);

			// Calibrate init gain for A path for TX0
			X = (rtl8192_QueryBBReg(dev, 0xe94, bMaskDWord) & 0x03FF0000)>>16;
			TXA[RF90_PATH_A] = (X * old_value)/0x100;
			reg = rtl8192_QueryBBReg(dev, 0xc80, bMaskDWord);
			reg = (reg & 0xFFFFFC00) | (u32)TXA[RF90_PATH_A];
			rtl8192_setBBreg(dev, 0xc80, bMaskDWord, reg);
			udelay(5);

			// Calibrate init gain for C path for TX0
			Y = ( rtl8192_QueryBBReg(dev, 0xe9C, bMaskDWord) & 0x03FF0000)>>16;
			TX0[RF90_PATH_C] = ((Y * old_value)/0x100);
			reg = rtl8192_QueryBBReg(dev, 0xc80, bMaskDWord);
			reg = (reg & 0xffc0ffff) |((u32) (TX0[RF90_PATH_C]&0x3F)<<16);
			rtl8192_setBBreg(dev, 0xc80, bMaskDWord, reg);
			reg = rtl8192_QueryBBReg(dev, 0xc94, bMaskDWord);
			reg = (reg & 0x0fffffff) |(((Y&0x3c0)>>6)<<28);
			rtl8192_setBBreg(dev, 0xc94, bMaskDWord, reg);
			udelay(5);

			// Calibrate RX A and B for RX0
			reg = rtl8192_QueryBBReg(dev, 0xc14, bMaskDWord);
			X = (rtl8192_QueryBBReg(dev, 0xea4, bMaskDWord) & 0x03FF0000)>>16;
			reg = (reg & 0xFFFFFC00) |X;
			rtl8192_setBBreg(dev, 0xc14, bMaskDWord, reg);
			Y = (rtl8192_QueryBBReg(dev, 0xeac, bMaskDWord) & 0x003F0000)>>16;
			reg = (reg & 0xFFFF03FF) |Y<<10;
			rtl8192_setBBreg(dev, 0xc14, bMaskDWord, reg);
			udelay(5);
			old_value = (rtl8192_QueryBBReg(dev, 0xc88, bMaskDWord) & 0x3FF);

			// Calibrate init gain for A path for TX1 !!!!!!
			X = (rtl8192_QueryBBReg(dev, 0xeb4, bMaskDWord) & 0x03FF0000)>>16;
			reg = rtl8192_QueryBBReg(dev, 0xc88, bMaskDWord);
			TXA[RF90_PATH_A] = (X * old_value) / 0x100;
			reg = (reg & 0xFFFFFC00) | TXA[RF90_PATH_A];
			rtl8192_setBBreg(dev, 0xc88, bMaskDWord, reg);
			udelay(5);

			// Calibrate init gain for C path for TX1
			Y = (rtl8192_QueryBBReg(dev, 0xebc, bMaskDWord)& 0x03FF0000)>>16;
			TX0[RF90_PATH_C] = ((Y * old_value)/0x100);
			reg = rtl8192_QueryBBReg(dev, 0xc88, bMaskDWord);
			reg = (reg & 0xffc0ffff) |( (TX0[RF90_PATH_C]&0x3F)<<16);
			rtl8192_setBBreg(dev, 0xc88, bMaskDWord, reg);
			reg = rtl8192_QueryBBReg(dev, 0xc9c, bMaskDWord);
			reg = (reg & 0x0fffffff) |(((Y&0x3c0)>>6)<<28);
			rtl8192_setBBreg(dev, 0xc9c, bMaskDWord, reg);
			udelay(5);

			// Calibrate RX A and B for RX1
			reg = rtl8192_QueryBBReg(dev, 0xc1c, bMaskDWord);
			X = (rtl8192_QueryBBReg(dev, 0xec4, bMaskDWord) & 0x03FF0000)>>16;
			reg = (reg & 0xFFFFFC00) |X;
			rtl8192_setBBreg(dev, 0xc1c, bMaskDWord, reg);

			Y = (rtl8192_QueryBBReg(dev, 0xecc, bMaskDWord) & 0x003F0000)>>16;
			reg = (reg & 0xFFFF03FF) |Y<<10;
			rtl8192_setBBreg(dev, 0xc1c, bMaskDWord, reg);
			udelay(5);

			RT_TRACE(COMP_INIT, "PHY_IQCalibrate OK\n");
			break;
		}

	}

	//
	// 4. Reload e70~ee0 register setting.
	//
	//RT_TRACE(COMP_INIT, DBG_LOUD, ("Reload e70~ee0 register setting.\n"));
	for (i = 0; i < 13; i++)
		rtl8192_setBBreg(dev, calibrate_set[i], bMaskDWord, load_value[i]);


	//
	// 3. QFN64. Not enabled now !!! We must use different gain table for 1T2R.
	//



}