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
 int BY_AL2230_REG_LEN ; 
 int CB_AL2230_INIT_SEQ ; 
 scalar_t__ IFREGCTL_REGW ; 
 int /*<<< orphan*/  IFRFbWriteEmbeded (scalar_t__,scalar_t__) ; 
 scalar_t__ MAC_REG_PSPWRSIG ; 
 scalar_t__ MAC_REG_SOFTPWRCTL ; 
 int /*<<< orphan*/  MACvTimer0MicroSDelay (scalar_t__,int) ; 
 int /*<<< orphan*/  MACvWordRegBitsOff (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  MACvWordRegBitsOn (scalar_t__,scalar_t__,int) ; 
 int PSSIG_WPE2 ; 
 int PSSIG_WPE3 ; 
 int SOFTPWRCTL_SWPE2 ; 
 int SOFTPWRCTL_SWPE3 ; 
 int SOFTPWRCTL_SWPECTI ; 
 int SOFTPWRCTL_TXPEINV ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int) ; 
 scalar_t__* dwAL2230InitTable ; 

BOOL RFbAL2230Init (DWORD_PTR dwIoBase)
{
    int     ii;
    BOOL    bResult;

    bResult = TRUE;

    //3-wire control for normal mode
    VNSvOutPortB(dwIoBase + MAC_REG_SOFTPWRCTL, 0);

    MACvWordRegBitsOn(dwIoBase, MAC_REG_SOFTPWRCTL, (SOFTPWRCTL_SWPECTI  |
                                                     SOFTPWRCTL_TXPEINV));
//2008-8-21 chester <add>
    // PLL  Off

    MACvWordRegBitsOff(dwIoBase, MAC_REG_SOFTPWRCTL, SOFTPWRCTL_SWPE3);



    //patch abnormal AL2230 frequency output
//2008-8-21 chester <add>
    IFRFbWriteEmbeded(dwIoBase, (0x07168700+(BY_AL2230_REG_LEN<<3)+IFREGCTL_REGW));


    for (ii = 0; ii < CB_AL2230_INIT_SEQ; ii++)
        bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL2230InitTable[ii]);
//2008-8-21 chester <add>
MACvTimer0MicroSDelay(dwIoBase, 30); //delay 30 us

    // PLL On
    MACvWordRegBitsOn(dwIoBase, MAC_REG_SOFTPWRCTL, SOFTPWRCTL_SWPE3);

    MACvTimer0MicroSDelay(dwIoBase, 150);//150us
    bResult &= IFRFbWriteEmbeded(dwIoBase, (0x00d80f00+(BY_AL2230_REG_LEN<<3)+IFREGCTL_REGW));
    MACvTimer0MicroSDelay(dwIoBase, 30);//30us
    bResult &= IFRFbWriteEmbeded(dwIoBase, (0x00780f00+(BY_AL2230_REG_LEN<<3)+IFREGCTL_REGW));
    MACvTimer0MicroSDelay(dwIoBase, 30);//30us
    bResult &= IFRFbWriteEmbeded(dwIoBase, dwAL2230InitTable[CB_AL2230_INIT_SEQ-1]);

    MACvWordRegBitsOn(dwIoBase, MAC_REG_SOFTPWRCTL, (SOFTPWRCTL_SWPE3    |
                                                     SOFTPWRCTL_SWPE2    |
                                                     SOFTPWRCTL_SWPECTI  |
                                                     SOFTPWRCTL_TXPEINV));

    //3-wire control for power saving mode
    VNSvOutPortB(dwIoBase + MAC_REG_PSPWRSIG, (PSSIG_WPE3 | PSSIG_WPE2)); //1100 0000

    return bResult;
}