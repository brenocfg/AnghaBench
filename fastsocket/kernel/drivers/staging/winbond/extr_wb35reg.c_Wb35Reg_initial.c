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
typedef  scalar_t__ u16 ;
struct wb35_reg {int EEPROMPhyType; int EEPROMRegion; int /*<<< orphan*/  EP0VM_spin_lock; } ;
struct hw_data {scalar_t__ phy_type; int PowerIndexFromEEPROM; int VCO_trim; int Scan_Interval; scalar_t__ SurpriseRemove; scalar_t__ SoftwareSet; int /*<<< orphan*/  PermanentMacAddress; int /*<<< orphan*/  CurrentMacAddress; struct wb35_reg reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBProcessor_initial (struct hw_data*) ; 
 int /*<<< orphan*/  Dxx_initial (struct hw_data*) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GetTxVgaFromEEPROM (struct hw_data*) ; 
 int /*<<< orphan*/  Mxx_initial (struct hw_data*) ; 
 int REGION_AUTO ; 
 int /*<<< orphan*/  RFSynthesizer_initial (struct hw_data*) ; 
 scalar_t__ RF_AIROHA_2230 ; 
 scalar_t__ RF_AIROHA_2230S ; 
 scalar_t__ RF_AIROHA_7230 ; 
 scalar_t__ RF_DECIDE_BY_INF ; 
 scalar_t__ RF_MAXIM_2825 ; 
 scalar_t__ RF_MAXIM_2827 ; 
 scalar_t__ RF_MAXIM_2828 ; 
 scalar_t__ RF_MAXIM_2829 ; 
 scalar_t__ RF_MAXIM_V1 ; 
 scalar_t__ RF_WB_242 ; 
 scalar_t__ RF_WB_242_1 ; 
 int SCAN_MAX_CHNL_TIME ; 
 int /*<<< orphan*/  Uxx_ReadEthernetAddress (struct hw_data*) ; 
 int /*<<< orphan*/  Uxx_power_on_procedure (struct hw_data*) ; 
 int /*<<< orphan*/  Wb35Reg_ReadSync (struct hw_data*,int,int*) ; 
 int /*<<< orphan*/  Wb35Reg_WriteSync (struct hw_data*,int,int) ; 
 int /*<<< orphan*/  Wb35Reg_phy_calibration (struct hw_data*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

unsigned char Wb35Reg_initial(struct hw_data * pHwData)
{
	struct wb35_reg *reg=&pHwData->reg;
	u32 ltmp;
	u32 SoftwareSet, VCO_trim, TxVga, Region_ScanInterval;

	// Spin lock is acquired for read and write IRP command
	spin_lock_init( &reg->EP0VM_spin_lock );

	// Getting RF module type from EEPROM ------------------------------------
	Wb35Reg_WriteSync( pHwData, 0x03b4, 0x080d0000 ); // Start EEPROM access + Read + address(0x0d)
	Wb35Reg_ReadSync( pHwData, 0x03b4, &ltmp );

	//Update RF module type and determine the PHY type by inf or EEPROM
	reg->EEPROMPhyType = (u8)( ltmp & 0xff );
	// 0 V MAX2825, 1 V MAX2827, 2 V MAX2828, 3 V MAX2829
	// 16V AL2230, 17 - AL7230, 18 - AL2230S
	// 32 Reserved
	// 33 - W89RF242(TxVGA 0~19), 34 - W89RF242(TxVGA 0~34)
	if (reg->EEPROMPhyType != RF_DECIDE_BY_INF) {
		if( (reg->EEPROMPhyType == RF_MAXIM_2825)	||
			(reg->EEPROMPhyType == RF_MAXIM_2827)	||
			(reg->EEPROMPhyType == RF_MAXIM_2828)	||
			(reg->EEPROMPhyType == RF_MAXIM_2829)	||
			(reg->EEPROMPhyType == RF_MAXIM_V1)	||
			(reg->EEPROMPhyType == RF_AIROHA_2230)	||
			(reg->EEPROMPhyType == RF_AIROHA_2230S)    ||
			(reg->EEPROMPhyType == RF_AIROHA_7230)	||
			(reg->EEPROMPhyType == RF_WB_242)		||
			(reg->EEPROMPhyType == RF_WB_242_1))
			pHwData->phy_type = reg->EEPROMPhyType;
	}

	// Power On procedure running. The relative parameter will be set according to phy_type
	Uxx_power_on_procedure( pHwData );

	// Reading MAC address
	Uxx_ReadEthernetAddress( pHwData );

	// Read VCO trim for RF parameter
	Wb35Reg_WriteSync( pHwData, 0x03b4, 0x08200000 );
	Wb35Reg_ReadSync( pHwData, 0x03b4, &VCO_trim );

	// Read Antenna On/Off of software flag
	Wb35Reg_WriteSync( pHwData, 0x03b4, 0x08210000 );
	Wb35Reg_ReadSync( pHwData, 0x03b4, &SoftwareSet );

	// Read TXVGA
	Wb35Reg_WriteSync( pHwData, 0x03b4, 0x08100000 );
	Wb35Reg_ReadSync( pHwData, 0x03b4, &TxVga );

	// Get Scan interval setting from EEPROM offset 0x1c
	Wb35Reg_WriteSync( pHwData, 0x03b4, 0x081d0000 );
	Wb35Reg_ReadSync( pHwData, 0x03b4, &Region_ScanInterval );

	// Update Ethernet address
	memcpy( pHwData->CurrentMacAddress, pHwData->PermanentMacAddress, ETH_ALEN );

	// Update software variable
	pHwData->SoftwareSet = (u16)(SoftwareSet & 0xffff);
	TxVga &= 0x000000ff;
	pHwData->PowerIndexFromEEPROM = (u8)TxVga;
	pHwData->VCO_trim = (u8)VCO_trim & 0xff;
	if (pHwData->VCO_trim == 0xff)
		pHwData->VCO_trim = 0x28;

	reg->EEPROMRegion = (u8)(Region_ScanInterval>>8); // 20060720
	if( reg->EEPROMRegion<1 || reg->EEPROMRegion>6 )
		reg->EEPROMRegion = REGION_AUTO;

	//For Get Tx VGA from EEPROM 20060315.5 move here
	GetTxVgaFromEEPROM( pHwData );

	// Set Scan Interval
	pHwData->Scan_Interval = (u8)(Region_ScanInterval & 0xff) * 10;
	if ((pHwData->Scan_Interval == 2550) || (pHwData->Scan_Interval < 10)) // Is default setting 0xff * 10
		pHwData->Scan_Interval = SCAN_MAX_CHNL_TIME;

	// Initial register
	RFSynthesizer_initial(pHwData);

	BBProcessor_initial(pHwData); // Async write, must wait until complete

	Wb35Reg_phy_calibration(pHwData);

	Mxx_initial(pHwData);
	Dxx_initial(pHwData);

	if (pHwData->SurpriseRemove)
		return false;
	else
		return true; // Initial fail
}