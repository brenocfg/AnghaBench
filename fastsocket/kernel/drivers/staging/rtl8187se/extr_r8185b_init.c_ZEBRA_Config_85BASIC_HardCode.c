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
typedef  int u8 ;
typedef  int u32 ;
struct r8180_priv {scalar_t__ card_8185; int XtalCal_Xin; int XtalCal_Xout; int /*<<< orphan*/  bSwAntennaDiverity; int /*<<< orphan*/  bDefaultAntenna1; scalar_t__ bXtalCalibration; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ANTSEL ; 
 int BIT11 ; 
 int BIT5 ; 
 int BIT6 ; 
 int BIT9 ; 
 int CCK_TXAGC ; 
 int* OFDM_CONFIG ; 
 int OFDM_TXAGC ; 
 int /*<<< orphan*/  PhyAddr ; 
 int /*<<< orphan*/  PlatformIOWrite4Byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int RF_ReadReg (struct net_device*,int) ; 
 int /*<<< orphan*/  RF_WriteReg (struct net_device*,int,int) ; 
 int /*<<< orphan*/  SetAntennaConfig87SE (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VERSION_8187S_C ; 
 scalar_t__ VERSION_8187S_D ; 
 int /*<<< orphan*/  WriteBBPortUchar (struct net_device*,int) ; 
 int* ZEBRA_AGC ; 
 int* ZEBRA_RF_RX_GAIN_TABLE ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int read_nic_byte (struct net_device*,int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_phy_cck (struct net_device*,int,int) ; 
 int /*<<< orphan*/  write_phy_ofdm (struct net_device*,int,int) ; 

void
ZEBRA_Config_85BASIC_HardCode(
	struct net_device *dev
	)
{

	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	u32			i;
	u32	addr,data;
	u32	u4bRegOffset, u4bRegValue, u4bRF23, u4bRF24;
       u8			u1b24E;


	//=============================================================================
	// 87S_PCIE :: RADIOCFG.TXT
	//=============================================================================


	// Page1 : reg16-reg30
	RF_WriteReg(dev, 0x00, 0x013f);			mdelay(1); // switch to page1
	u4bRF23= RF_ReadReg(dev, 0x08);			mdelay(1);
	u4bRF24= RF_ReadReg(dev, 0x09);			mdelay(1);

	if (u4bRF23==0x818 && u4bRF24==0x70C && priv->card_8185 == VERSION_8187S_C)
		priv->card_8185 = VERSION_8187S_D;

	// Page0 : reg0-reg15

//	RF_WriteReg(dev, 0x00, 0x003f);			mdelay(1);//1
	RF_WriteReg(dev, 0x00, 0x009f);      	mdelay(1);// 1

	RF_WriteReg(dev, 0x01, 0x06e0);			mdelay(1);

//	RF_WriteReg(dev, 0x02, 0x004c);			mdelay(1);//2
	RF_WriteReg(dev, 0x02, 0x004d);			mdelay(1);// 2

//	RF_WriteReg(dev, 0x03, 0x0000);			mdelay(1);//3
	RF_WriteReg(dev, 0x03, 0x07f1);			mdelay(1);// 3

	RF_WriteReg(dev, 0x04, 0x0975);			mdelay(1);
	RF_WriteReg(dev, 0x05, 0x0c72);			mdelay(1);
	RF_WriteReg(dev, 0x06, 0x0ae6);			mdelay(1);
	RF_WriteReg(dev, 0x07, 0x00ca);			mdelay(1);
	RF_WriteReg(dev, 0x08, 0x0e1c);			mdelay(1);
	RF_WriteReg(dev, 0x09, 0x02f0);			mdelay(1);
	RF_WriteReg(dev, 0x0a, 0x09d0);			mdelay(1);
	RF_WriteReg(dev, 0x0b, 0x01ba);			mdelay(1);
	RF_WriteReg(dev, 0x0c, 0x0640);			mdelay(1);
	RF_WriteReg(dev, 0x0d, 0x08df);			mdelay(1);
	RF_WriteReg(dev, 0x0e, 0x0020);			mdelay(1);
	RF_WriteReg(dev, 0x0f, 0x0990);			mdelay(1);


	// Page1 : reg16-reg30
	RF_WriteReg(dev, 0x00, 0x013f);			mdelay(1);

	RF_WriteReg(dev, 0x03, 0x0806);			mdelay(1);

	if(priv->card_8185 < VERSION_8187S_C)
	{
		RF_WriteReg(dev, 0x04, 0x03f7);			mdelay(1);
		RF_WriteReg(dev, 0x05, 0x05ab);			mdelay(1);
		RF_WriteReg(dev, 0x06, 0x00c1);			mdelay(1);
	}
	else
	{
		RF_WriteReg(dev, 0x04, 0x03a7);			mdelay(1);
		RF_WriteReg(dev, 0x05, 0x059b);			mdelay(1);
		RF_WriteReg(dev, 0x06, 0x0081);			mdelay(1);
	}


	RF_WriteReg(dev, 0x07, 0x01A0);			mdelay(1);
// Don't write RF23/RF24 to make a difference between 87S C cut and D cut. asked by SD3 stevenl.
//	RF_WriteReg(dev, 0x08, 0x0597);			mdelay(1);
//	RF_WriteReg(dev, 0x09, 0x050a);			mdelay(1);
	RF_WriteReg(dev, 0x0a, 0x0001);			mdelay(1);
	RF_WriteReg(dev, 0x0b, 0x0418);			mdelay(1);

	if(priv->card_8185 == VERSION_8187S_D)
	{
		RF_WriteReg(dev, 0x0c, 0x0fbe);			mdelay(1);
		RF_WriteReg(dev, 0x0d, 0x0008);			mdelay(1);
		RF_WriteReg(dev, 0x0e, 0x0807);			mdelay(1); // RX LO buffer
	}
	else
	{
		RF_WriteReg(dev, 0x0c, 0x0fbe);			mdelay(1);
		RF_WriteReg(dev, 0x0d, 0x0008);			mdelay(1);
		RF_WriteReg(dev, 0x0e, 0x0806);			mdelay(1); // RX LO buffer
	}

	RF_WriteReg(dev, 0x0f, 0x0acc);			mdelay(1);

//	RF_WriteReg(dev, 0x00, 0x017f);			mdelay(1);//6
	RF_WriteReg(dev, 0x00, 0x01d7);			mdelay(1);// 6

	RF_WriteReg(dev, 0x03, 0x0e00);			mdelay(1);
	RF_WriteReg(dev, 0x04, 0x0e50);			mdelay(1);
	for(i=0;i<=36;i++)
	{
		RF_WriteReg(dev, 0x01, i);                     mdelay(1);
		RF_WriteReg(dev, 0x02, ZEBRA_RF_RX_GAIN_TABLE[i]); mdelay(1);
		//DbgPrint("RF - 0x%x = 0x%x", i, ZEBRA_RF_RX_GAIN_TABLE[i]);
	}

	RF_WriteReg(dev, 0x05, 0x0203);			mdelay(1); 	/// 203, 343
	//RF_WriteReg(dev, 0x06, 0x0300);			mdelay(1);	// 400
	RF_WriteReg(dev, 0x06, 0x0200);			mdelay(1);	// 400

	RF_WriteReg(dev, 0x00, 0x0137);			mdelay(1);	// switch to reg16-reg30, and HSSI disable 137
	mdelay(10); 	// Deay 10 ms. //0xfd

//	RF_WriteReg(dev, 0x0c, 0x09be);			mdelay(1);	// 7
	//RF_WriteReg(dev, 0x0c, 0x07be);			mdelay(1);
	//mdelay(10); 	// Deay 10 ms. //0xfd

	RF_WriteReg(dev, 0x0d, 0x0008);			mdelay(1);	// Z4 synthesizer loop filter setting, 392
	mdelay(10); 	// Deay 10 ms. //0xfd

	RF_WriteReg(dev, 0x00, 0x0037);			mdelay(1);	// switch to reg0-reg15, and HSSI disable
	mdelay(10); 	// Deay 10 ms. //0xfd

	RF_WriteReg(dev, 0x04, 0x0160);			mdelay(1); 	// CBC on, Tx Rx disable, High gain
	mdelay(10); 	// Deay 10 ms. //0xfd

	RF_WriteReg(dev, 0x07, 0x0080);			mdelay(1);	// Z4 setted channel 1
	mdelay(10); 	// Deay 10 ms. //0xfd

	RF_WriteReg(dev, 0x02, 0x088D);			mdelay(1);	// LC calibration
	mdelay(200); 	// Deay 200 ms. //0xfd
	mdelay(10); 	// Deay 10 ms. //0xfd
	mdelay(10); 	// Deay 10 ms. //0xfd

	RF_WriteReg(dev, 0x00, 0x0137);			mdelay(1);	// switch to reg16-reg30 137, and HSSI disable 137
	mdelay(10); 	// Deay 10 ms. //0xfd

	RF_WriteReg(dev, 0x07, 0x0000);			mdelay(1);
	RF_WriteReg(dev, 0x07, 0x0180);			mdelay(1);
	RF_WriteReg(dev, 0x07, 0x0220);			mdelay(1);
	RF_WriteReg(dev, 0x07, 0x03E0);			mdelay(1);

	// DAC calibration off 20070702
	RF_WriteReg(dev, 0x06, 0x00c1);			mdelay(1);
	RF_WriteReg(dev, 0x0a, 0x0001);			mdelay(1);
//{by amy 080312
	// For crystal calibration, added by Roger, 2007.12.11.
	if( priv->bXtalCalibration ) // reg 30.
	{ // enable crystal calibration.
		// RF Reg[30], (1)Xin:[12:9], Xout:[8:5],  addr[4:0].
		// (2)PA Pwr delay timer[15:14], default: 2.4us, set BIT15=0
		// (3)RF signal on/off when calibration[13], default: on, set BIT13=0.
		// So we should minus 4 BITs offset.
		RF_WriteReg(dev, 0x0f, (priv->XtalCal_Xin<<5)|(priv->XtalCal_Xout<<1)|BIT11|BIT9);			mdelay(1);
		printk("ZEBRA_Config_85BASIC_HardCode(): (%02x)\n",
				(priv->XtalCal_Xin<<5) | (priv->XtalCal_Xout<<1) | BIT11| BIT9);
	}
	else
	{ // using default value. Xin=6, Xout=6.
		RF_WriteReg(dev, 0x0f, 0x0acc);			mdelay(1);
	}
//by amy 080312
//	RF_WriteReg(dev, 0x0f, 0x0acc);			mdelay(1);  //-by amy 080312

	RF_WriteReg(dev, 0x00, 0x00bf);			mdelay(1); // switch to reg0-reg15, and HSSI enable
//	RF_WriteReg(dev, 0x0d, 0x009f);			mdelay(1); // Rx BB start calibration, 00c//-edward
	RF_WriteReg(dev, 0x0d, 0x08df);			mdelay(1); // Rx BB start calibration, 00c//+edward
	RF_WriteReg(dev, 0x02, 0x004d);			mdelay(1); // temperature meter off
	RF_WriteReg(dev, 0x04, 0x0975);			mdelay(1); // Rx mode
	mdelay(10);	// Deay 10 ms. //0xfe
	mdelay(10);	// Deay 10 ms. //0xfe
	mdelay(10);	// Deay 10 ms. //0xfe
	RF_WriteReg(dev, 0x00, 0x0197);			mdelay(1); // Rx mode//+edward
	RF_WriteReg(dev, 0x05, 0x05ab);			mdelay(1); // Rx mode//+edward
	RF_WriteReg(dev, 0x00, 0x009f);			mdelay(1); // Rx mode//+edward

	RF_WriteReg(dev, 0x01, 0x0000);			mdelay(1); // Rx mode//+edward
	RF_WriteReg(dev, 0x02, 0x0000);			mdelay(1); // Rx mode//+edward
	//power save parameters.
	u1b24E = read_nic_byte(dev, 0x24E);
	write_nic_byte(dev, 0x24E, (u1b24E & (~(BIT5|BIT6))));

	//=============================================================================

	//=============================================================================
	// CCKCONF.TXT
	//=============================================================================

	/*	[POWER SAVE] Power Saving Parameters by jong. 2007-11-27
	   	CCK reg0x00[7]=1'b1 :power saving for TX (default)
		CCK reg0x00[6]=1'b1: power saving for RX (default)
		CCK reg0x06[4]=1'b1: turn off channel estimation related circuits if not doing channel estimation.
		CCK reg0x06[3]=1'b1: turn off unused circuits before cca = 1
		CCK reg0x06[2]=1'b1: turn off cck's circuit if macrst =0
	*/

	write_phy_cck(dev,0x00,0xc8);
	write_phy_cck(dev,0x06,0x1c);
	write_phy_cck(dev,0x10,0x78);
	write_phy_cck(dev,0x2e,0xd0);
	write_phy_cck(dev,0x2f,0x06);
	write_phy_cck(dev,0x01,0x46);

	// power control
	write_nic_byte(dev, CCK_TXAGC, 0x10);
	write_nic_byte(dev, OFDM_TXAGC, 0x1B);
	write_nic_byte(dev, ANTSEL, 0x03);



	//=============================================================================
	// AGC.txt
	//=============================================================================

//	PlatformIOWrite4Byte( dev, PhyAddr, 0x00001280);	// Annie, 2006-05-05
	write_phy_ofdm(dev, 0x00, 0x12);
	//WriteBBPortUchar(dev, 0x00001280);

	for (i=0; i<128; i++)
	{
		//DbgPrint("AGC - [%x+1] = 0x%x\n", i, ZEBRA_AGC[i+1]);

		data = ZEBRA_AGC[i+1];
		data = data << 8;
		data = data | 0x0000008F;

		addr = i + 0x80; //enable writing AGC table
		addr = addr << 8;
		addr = addr | 0x0000008E;

		WriteBBPortUchar(dev, data);
		WriteBBPortUchar(dev, addr);
		WriteBBPortUchar(dev, 0x0000008E);
	}

	PlatformIOWrite4Byte( dev, PhyAddr, 0x00001080);	// Annie, 2006-05-05
	//WriteBBPortUchar(dev, 0x00001080);

	//=============================================================================

	//=============================================================================
	// OFDMCONF.TXT
	//=============================================================================

	for(i=0; i<60; i++)
	{
		u4bRegOffset=i;
		u4bRegValue=OFDM_CONFIG[i];

		//DbgPrint("OFDM - 0x%x = 0x%x\n", u4bRegOffset, u4bRegValue);

		WriteBBPortUchar(dev,
						(0x00000080 |
						(u4bRegOffset & 0x7f) |
						((u4bRegValue & 0xff) << 8)));
	}

	//=============================================================================
//by amy for antenna
	//=============================================================================
//{by amy 080312
	// Config Sw/Hw  Combinational Antenna Diversity. Added by Roger, 2008.02.26.
	SetAntennaConfig87SE(dev, priv->bDefaultAntenna1, priv->bSwAntennaDiverity);
//by amy 080312}
//by amy for antenna
}