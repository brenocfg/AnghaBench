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

/* Variables and functions */
 scalar_t__ MAC_REG_PMC1 ; 
 scalar_t__ MAC_REG_TFTCTL ; 
 int /*<<< orphan*/  MACbSoftwareReset (scalar_t__) ; 
 int /*<<< orphan*/  MACvClearStckDS (scalar_t__) ; 
 int /*<<< orphan*/  MACvSetPacketFilter (scalar_t__,int) ; 
 int PKT_TYPE_BROADCAST ; 
 int PKT_TYPE_DIRECTED ; 
 int /*<<< orphan*/  PME_OVR ; 
 int /*<<< orphan*/  TFTCTL_TSFCNTREN ; 
 int /*<<< orphan*/  TFTCTL_TSFCNTRST ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int /*<<< orphan*/ ) ; 

void MACvInitialize (DWORD_PTR dwIoBase)
{
    // clear sticky bits
    MACvClearStckDS(dwIoBase);
    // disable force PME-enable
    VNSvOutPortB(dwIoBase + MAC_REG_PMC1, PME_OVR);
    // only 3253 A
    /*
    MACvPwrEvntDisable(dwIoBase);
    // clear power status
    VNSvOutPortW(dwIoBase + MAC_REG_WAKEUPSR0, 0x0F0F);
    */

    // do reset
    MACbSoftwareReset(dwIoBase);

    // issue AUTOLD in EECSR to reload eeprom
    //MACvRegBitsOn(dwIoBase, MAC_REG_I2MCSR, I2MCSR_AUTOLD);
    // wait until EEPROM loading complete
    //while (TRUE) {
    //    U8 u8Data;
    //    VNSvInPortB(dwIoBase + MAC_REG_I2MCSR, &u8Data);
    //    if ( !(u8Data & I2MCSR_AUTOLD))
    //        break;
    //}

    // reset TSF counter
    VNSvOutPortB(dwIoBase + MAC_REG_TFTCTL, TFTCTL_TSFCNTRST);
    // enable TSF counter
    VNSvOutPortB(dwIoBase + MAC_REG_TFTCTL, TFTCTL_TSFCNTREN);


    // set packet filter
    // receive directed and broadcast address

    MACvSetPacketFilter(dwIoBase, PKT_TYPE_DIRECTED | PKT_TYPE_BROADCAST);

}