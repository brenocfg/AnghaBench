#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct r8192_priv {TYPE_1__* PHYRegDef; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rfLSSIReadBack; int /*<<< orphan*/  rfTxAFE; int /*<<< orphan*/  rfTxIQImbalance; int /*<<< orphan*/  rfRxAFE; int /*<<< orphan*/  rfRxIQImbalance; int /*<<< orphan*/  rfAGCControl2; int /*<<< orphan*/  rfAGCControl1; void* rfSwitchControl; int /*<<< orphan*/  rfHSSIPara2; int /*<<< orphan*/  rfHSSIPara1; void* rfTxGainStage; void* rfLSSI_Select; int /*<<< orphan*/  rf3wireOffset; void* rfintfe; void* rfintfo; void* rfintfi; void* rfintfs; } ;

/* Variables and functions */
 size_t RF90_PATH_A ; 
 size_t RF90_PATH_B ; 
 size_t RF90_PATH_C ; 
 size_t RF90_PATH_D ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 void* rFPGA0_TxGainStage ; 
 void* rFPGA0_XAB_RFInterfaceRB ; 
 void* rFPGA0_XAB_RFInterfaceSW ; 
 void* rFPGA0_XAB_RFParameter ; 
 void* rFPGA0_XAB_SwitchControl ; 
 int /*<<< orphan*/  rFPGA0_XA_HSSIParameter1 ; 
 int /*<<< orphan*/  rFPGA0_XA_HSSIParameter2 ; 
 int /*<<< orphan*/  rFPGA0_XA_LSSIParameter ; 
 int /*<<< orphan*/  rFPGA0_XA_LSSIReadBack ; 
 void* rFPGA0_XA_RFInterfaceOE ; 
 int /*<<< orphan*/  rFPGA0_XB_HSSIParameter1 ; 
 int /*<<< orphan*/  rFPGA0_XB_HSSIParameter2 ; 
 int /*<<< orphan*/  rFPGA0_XB_LSSIParameter ; 
 int /*<<< orphan*/  rFPGA0_XB_LSSIReadBack ; 
 void* rFPGA0_XB_RFInterfaceOE ; 
 void* rFPGA0_XCD_RFInterfaceRB ; 
 void* rFPGA0_XCD_RFInterfaceSW ; 
 void* rFPGA0_XCD_RFParameter ; 
 void* rFPGA0_XCD_SwitchControl ; 
 int /*<<< orphan*/  rFPGA0_XC_HSSIParameter1 ; 
 int /*<<< orphan*/  rFPGA0_XC_HSSIParameter2 ; 
 int /*<<< orphan*/  rFPGA0_XC_LSSIParameter ; 
 int /*<<< orphan*/  rFPGA0_XC_LSSIReadBack ; 
 void* rFPGA0_XC_RFInterfaceOE ; 
 int /*<<< orphan*/  rFPGA0_XD_HSSIParameter1 ; 
 int /*<<< orphan*/  rFPGA0_XD_HSSIParameter2 ; 
 int /*<<< orphan*/  rFPGA0_XD_LSSIParameter ; 
 int /*<<< orphan*/  rFPGA0_XD_LSSIReadBack ; 
 void* rFPGA0_XD_RFInterfaceOE ; 
 int /*<<< orphan*/  rOFDM0_XAAGCCore1 ; 
 int /*<<< orphan*/  rOFDM0_XAAGCCore2 ; 
 int /*<<< orphan*/  rOFDM0_XARxAFE ; 
 int /*<<< orphan*/  rOFDM0_XARxIQImbalance ; 
 int /*<<< orphan*/  rOFDM0_XATxAFE ; 
 int /*<<< orphan*/  rOFDM0_XATxIQImbalance ; 
 int /*<<< orphan*/  rOFDM0_XBAGCCore1 ; 
 int /*<<< orphan*/  rOFDM0_XBAGCCore2 ; 
 int /*<<< orphan*/  rOFDM0_XBRxAFE ; 
 int /*<<< orphan*/  rOFDM0_XBRxIQImbalance ; 
 int /*<<< orphan*/  rOFDM0_XBTxAFE ; 
 int /*<<< orphan*/  rOFDM0_XBTxIQImbalance ; 
 int /*<<< orphan*/  rOFDM0_XCAGCCore1 ; 
 int /*<<< orphan*/  rOFDM0_XCAGCCore2 ; 
 int /*<<< orphan*/  rOFDM0_XCRxAFE ; 
 int /*<<< orphan*/  rOFDM0_XCRxIQImbalance ; 
 int /*<<< orphan*/  rOFDM0_XCTxAFE ; 
 int /*<<< orphan*/  rOFDM0_XCTxIQImbalance ; 
 int /*<<< orphan*/  rOFDM0_XDAGCCore1 ; 
 int /*<<< orphan*/  rOFDM0_XDAGCCore2 ; 
 int /*<<< orphan*/  rOFDM0_XDRxAFE ; 
 int /*<<< orphan*/  rOFDM0_XDRxIQImbalance ; 
 int /*<<< orphan*/  rOFDM0_XDTxAFE ; 
 int /*<<< orphan*/  rOFDM0_XDTxIQImbalance ; 

__attribute__((used)) static void rtl8192_InitBBRFRegDef(struct net_device* dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
// RF Interface Sowrtware Control
	priv->PHYRegDef[RF90_PATH_A].rfintfs = rFPGA0_XAB_RFInterfaceSW; // 16 LSBs if read 32-bit from 0x870
	priv->PHYRegDef[RF90_PATH_B].rfintfs = rFPGA0_XAB_RFInterfaceSW; // 16 MSBs if read 32-bit from 0x870 (16-bit for 0x872)
	priv->PHYRegDef[RF90_PATH_C].rfintfs = rFPGA0_XCD_RFInterfaceSW;// 16 LSBs if read 32-bit from 0x874
	priv->PHYRegDef[RF90_PATH_D].rfintfs = rFPGA0_XCD_RFInterfaceSW;// 16 MSBs if read 32-bit from 0x874 (16-bit for 0x876)

	// RF Interface Readback Value
	priv->PHYRegDef[RF90_PATH_A].rfintfi = rFPGA0_XAB_RFInterfaceRB; // 16 LSBs if read 32-bit from 0x8E0
	priv->PHYRegDef[RF90_PATH_B].rfintfi = rFPGA0_XAB_RFInterfaceRB;// 16 MSBs if read 32-bit from 0x8E0 (16-bit for 0x8E2)
	priv->PHYRegDef[RF90_PATH_C].rfintfi = rFPGA0_XCD_RFInterfaceRB;// 16 LSBs if read 32-bit from 0x8E4
	priv->PHYRegDef[RF90_PATH_D].rfintfi = rFPGA0_XCD_RFInterfaceRB;// 16 MSBs if read 32-bit from 0x8E4 (16-bit for 0x8E6)

	// RF Interface Output (and Enable)
	priv->PHYRegDef[RF90_PATH_A].rfintfo = rFPGA0_XA_RFInterfaceOE; // 16 LSBs if read 32-bit from 0x860
	priv->PHYRegDef[RF90_PATH_B].rfintfo = rFPGA0_XB_RFInterfaceOE; // 16 LSBs if read 32-bit from 0x864
	priv->PHYRegDef[RF90_PATH_C].rfintfo = rFPGA0_XC_RFInterfaceOE;// 16 LSBs if read 32-bit from 0x868
	priv->PHYRegDef[RF90_PATH_D].rfintfo = rFPGA0_XD_RFInterfaceOE;// 16 LSBs if read 32-bit from 0x86C

	// RF Interface (Output and)  Enable
	priv->PHYRegDef[RF90_PATH_A].rfintfe = rFPGA0_XA_RFInterfaceOE; // 16 MSBs if read 32-bit from 0x860 (16-bit for 0x862)
	priv->PHYRegDef[RF90_PATH_B].rfintfe = rFPGA0_XB_RFInterfaceOE; // 16 MSBs if read 32-bit from 0x864 (16-bit for 0x866)
	priv->PHYRegDef[RF90_PATH_C].rfintfe = rFPGA0_XC_RFInterfaceOE;// 16 MSBs if read 32-bit from 0x86A (16-bit for 0x86A)
	priv->PHYRegDef[RF90_PATH_D].rfintfe = rFPGA0_XD_RFInterfaceOE;// 16 MSBs if read 32-bit from 0x86C (16-bit for 0x86E)

	//Addr of LSSI. Wirte RF register by driver
	priv->PHYRegDef[RF90_PATH_A].rf3wireOffset = rFPGA0_XA_LSSIParameter; //LSSI Parameter
	priv->PHYRegDef[RF90_PATH_B].rf3wireOffset = rFPGA0_XB_LSSIParameter;
	priv->PHYRegDef[RF90_PATH_C].rf3wireOffset = rFPGA0_XC_LSSIParameter;
	priv->PHYRegDef[RF90_PATH_D].rf3wireOffset = rFPGA0_XD_LSSIParameter;

	// RF parameter
	priv->PHYRegDef[RF90_PATH_A].rfLSSI_Select = rFPGA0_XAB_RFParameter;  //BB Band Select
	priv->PHYRegDef[RF90_PATH_B].rfLSSI_Select = rFPGA0_XAB_RFParameter;
	priv->PHYRegDef[RF90_PATH_C].rfLSSI_Select = rFPGA0_XCD_RFParameter;
	priv->PHYRegDef[RF90_PATH_D].rfLSSI_Select = rFPGA0_XCD_RFParameter;

	// Tx AGC Gain Stage (same for all path. Should we remove this?)
	priv->PHYRegDef[RF90_PATH_A].rfTxGainStage = rFPGA0_TxGainStage; //Tx gain stage
	priv->PHYRegDef[RF90_PATH_B].rfTxGainStage = rFPGA0_TxGainStage; //Tx gain stage
	priv->PHYRegDef[RF90_PATH_C].rfTxGainStage = rFPGA0_TxGainStage; //Tx gain stage
	priv->PHYRegDef[RF90_PATH_D].rfTxGainStage = rFPGA0_TxGainStage; //Tx gain stage

	// Tranceiver A~D HSSI Parameter-1
	priv->PHYRegDef[RF90_PATH_A].rfHSSIPara1 = rFPGA0_XA_HSSIParameter1;  //wire control parameter1
	priv->PHYRegDef[RF90_PATH_B].rfHSSIPara1 = rFPGA0_XB_HSSIParameter1;  //wire control parameter1
	priv->PHYRegDef[RF90_PATH_C].rfHSSIPara1 = rFPGA0_XC_HSSIParameter1;  //wire control parameter1
	priv->PHYRegDef[RF90_PATH_D].rfHSSIPara1 = rFPGA0_XD_HSSIParameter1;  //wire control parameter1

	// Tranceiver A~D HSSI Parameter-2
	priv->PHYRegDef[RF90_PATH_A].rfHSSIPara2 = rFPGA0_XA_HSSIParameter2;  //wire control parameter2
	priv->PHYRegDef[RF90_PATH_B].rfHSSIPara2 = rFPGA0_XB_HSSIParameter2;  //wire control parameter2
	priv->PHYRegDef[RF90_PATH_C].rfHSSIPara2 = rFPGA0_XC_HSSIParameter2;  //wire control parameter2
	priv->PHYRegDef[RF90_PATH_D].rfHSSIPara2 = rFPGA0_XD_HSSIParameter2;  //wire control parameter1

	// RF switch Control
	priv->PHYRegDef[RF90_PATH_A].rfSwitchControl = rFPGA0_XAB_SwitchControl; //TR/Ant switch control
	priv->PHYRegDef[RF90_PATH_B].rfSwitchControl = rFPGA0_XAB_SwitchControl;
	priv->PHYRegDef[RF90_PATH_C].rfSwitchControl = rFPGA0_XCD_SwitchControl;
	priv->PHYRegDef[RF90_PATH_D].rfSwitchControl = rFPGA0_XCD_SwitchControl;

	// AGC control 1
	priv->PHYRegDef[RF90_PATH_A].rfAGCControl1 = rOFDM0_XAAGCCore1;
	priv->PHYRegDef[RF90_PATH_B].rfAGCControl1 = rOFDM0_XBAGCCore1;
	priv->PHYRegDef[RF90_PATH_C].rfAGCControl1 = rOFDM0_XCAGCCore1;
	priv->PHYRegDef[RF90_PATH_D].rfAGCControl1 = rOFDM0_XDAGCCore1;

	// AGC control 2
	priv->PHYRegDef[RF90_PATH_A].rfAGCControl2 = rOFDM0_XAAGCCore2;
	priv->PHYRegDef[RF90_PATH_B].rfAGCControl2 = rOFDM0_XBAGCCore2;
	priv->PHYRegDef[RF90_PATH_C].rfAGCControl2 = rOFDM0_XCAGCCore2;
	priv->PHYRegDef[RF90_PATH_D].rfAGCControl2 = rOFDM0_XDAGCCore2;

	// RX AFE control 1
	priv->PHYRegDef[RF90_PATH_A].rfRxIQImbalance = rOFDM0_XARxIQImbalance;
	priv->PHYRegDef[RF90_PATH_B].rfRxIQImbalance = rOFDM0_XBRxIQImbalance;
	priv->PHYRegDef[RF90_PATH_C].rfRxIQImbalance = rOFDM0_XCRxIQImbalance;
	priv->PHYRegDef[RF90_PATH_D].rfRxIQImbalance = rOFDM0_XDRxIQImbalance;

	// RX AFE control 1
	priv->PHYRegDef[RF90_PATH_A].rfRxAFE = rOFDM0_XARxAFE;
	priv->PHYRegDef[RF90_PATH_B].rfRxAFE = rOFDM0_XBRxAFE;
	priv->PHYRegDef[RF90_PATH_C].rfRxAFE = rOFDM0_XCRxAFE;
	priv->PHYRegDef[RF90_PATH_D].rfRxAFE = rOFDM0_XDRxAFE;

	// Tx AFE control 1
	priv->PHYRegDef[RF90_PATH_A].rfTxIQImbalance = rOFDM0_XATxIQImbalance;
	priv->PHYRegDef[RF90_PATH_B].rfTxIQImbalance = rOFDM0_XBTxIQImbalance;
	priv->PHYRegDef[RF90_PATH_C].rfTxIQImbalance = rOFDM0_XCTxIQImbalance;
	priv->PHYRegDef[RF90_PATH_D].rfTxIQImbalance = rOFDM0_XDTxIQImbalance;

	// Tx AFE control 2
	priv->PHYRegDef[RF90_PATH_A].rfTxAFE = rOFDM0_XATxAFE;
	priv->PHYRegDef[RF90_PATH_B].rfTxAFE = rOFDM0_XBTxAFE;
	priv->PHYRegDef[RF90_PATH_C].rfTxAFE = rOFDM0_XCTxAFE;
	priv->PHYRegDef[RF90_PATH_D].rfTxAFE = rOFDM0_XDTxAFE;

	// Tranceiver LSSI Readback
	priv->PHYRegDef[RF90_PATH_A].rfLSSIReadBack = rFPGA0_XA_LSSIReadBack;
	priv->PHYRegDef[RF90_PATH_B].rfLSSIReadBack = rFPGA0_XB_LSSIReadBack;
	priv->PHYRegDef[RF90_PATH_C].rfLSSIReadBack = rFPGA0_XC_LSSIReadBack;
	priv->PHYRegDef[RF90_PATH_D].rfLSSIReadBack = rFPGA0_XD_LSSIReadBack;

}