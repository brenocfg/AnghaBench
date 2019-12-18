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
typedef  scalar_t__ DWORD_PTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BBvPowerSaveModeOFF (scalar_t__) ; 
 int /*<<< orphan*/  BBvPowerSaveModeON (scalar_t__) ; 
 int BY_AL7230_REG_LEN ; 
 int CB_AL7230_INIT_SEQ ; 
 scalar_t__ IFREGCTL_REGW ; 
 int /*<<< orphan*/  IFRFbWriteEmbeded (scalar_t__,scalar_t__) ; 
 scalar_t__ MAC_REG_PSPWRSIG ; 
 scalar_t__ MAC_REG_SOFTPWRCTL ; 
 int /*<<< orphan*/  MACvTimer0MicroSDelay (scalar_t__,int) ; 
 int /*<<< orphan*/  MACvWordRegBitsOn (scalar_t__,scalar_t__,int) ; 
 int PSSIG_WPE2 ; 
 int PSSIG_WPE3 ; 
 int SOFTPWRCTL_SWPE2 ; 
 int SOFTPWRCTL_SWPE3 ; 
 int SOFTPWRCTL_SWPECTI ; 
 int SOFTPWRCTL_TXPEINV ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int) ; 
 scalar_t__* dwAL7230InitTable ; 

BOOL s_bAL7230Init (DWORD_PTR dwIoBase)
{
    int     ii;
    BOOL    bResult;

    bResult = TRUE;

    //3-wire control for normal mode
    VNSvOutPortB(dwIoBase + MAC_REG_SOFTPWRCTL, 0);

    MACvWordRegBitsOn(dwIoBase, MAC_REG_SOFTPWRCTL, (SOFTPWRCTL_SWPECTI  |
                                                     SOFTPWRCTL_TXPEINV));
    BBvPowerSaveModeOFF(dwIoBase); //RobertYu:20050106, have DC value for Calibration

    for (ii = 0; ii < CB_AL7230_INIT_SEQ; ii++)
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTable[ii]);

    // PLL On
    MACvWordRegBitsOn(dwIoBase, MAC_REG_SOFTPWRCTL, SOFTPWRCTL_SWPE3);

    //Calibration
    MACvTimer0MicroSDelay(dwIoBase, 150);//150us
    bResult &= IFRFbWriteEmbeded(dwIoBase, (0x9ABA8F00+(BY_AL7230_REG_LEN<<3)+IFREGCTL_REGW)); //TXDCOC:active, RCK:diable
    MACvTimer0MicroSDelay(dwIoBase, 30);//30us
    bResult &= IFRFbWriteEmbeded(dwIoBase, (0x3ABA8F00+(BY_AL7230_REG_LEN<<3)+IFREGCTL_REGW)); //TXDCOC:diable, RCK:active
    MACvTimer0MicroSDelay(dwIoBase, 30);//30us
    bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL7230InitTable[CB_AL7230_INIT_SEQ-1]); //TXDCOC:diable, RCK:diable

    MACvWordRegBitsOn(dwIoBase, MAC_REG_SOFTPWRCTL, (SOFTPWRCTL_SWPE3    |
                                                     SOFTPWRCTL_SWPE2    |
                                                     SOFTPWRCTL_SWPECTI  |
                                                     SOFTPWRCTL_TXPEINV));

    BBvPowerSaveModeON(dwIoBase); // RobertYu:20050106

    // PE1: TX_ON, PE2: RX_ON, PE3: PLLON
    //3-wire control for power saving mode
    VNSvOutPortB(dwIoBase + MAC_REG_PSPWRSIG, (PSSIG_WPE3 | PSSIG_WPE2)); //1100 0000

    return bResult;
}