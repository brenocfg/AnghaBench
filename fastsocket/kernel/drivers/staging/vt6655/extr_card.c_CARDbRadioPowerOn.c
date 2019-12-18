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
struct TYPE_2__ {scalar_t__ bRadioControlOff; scalar_t__ bHWRadioOff; scalar_t__ bRadioOff; int byRFType; int /*<<< orphan*/  PortOffset; int /*<<< orphan*/  byLocalID; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSDevice ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BBvExitDeepSleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HOSTCR_RXON ; 
 int /*<<< orphan*/  LED_ACTSET ; 
 int /*<<< orphan*/  MAC_REG_GPIOCTL0 ; 
 int /*<<< orphan*/  MAC_REG_HOSTCR ; 
 int /*<<< orphan*/  MAC_REG_SOFTPWRCTL ; 
 int /*<<< orphan*/  MACvRegBitsOff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvRegBitsOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvWordRegBitsOff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvWordRegBitsOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  RF_AIROHA 131 
#define  RF_AIROHA7230 130 
#define  RF_AL2230S 129 
#define  RF_RFMD2959 128 
 int /*<<< orphan*/  SOFTPWRCTL_SWPE1 ; 
 int SOFTPWRCTL_SWPE2 ; 
 int SOFTPWRCTL_SWPE3 ; 
 int SOFTPWRCTL_TXPEINV ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  printk (char*) ; 

BOOL CARDbRadioPowerOn (PVOID pDeviceHandler)
{
    PSDevice    pDevice = (PSDevice) pDeviceHandler;
    BOOL        bResult = TRUE;
printk("chester power on\n");
    if (pDevice->bRadioControlOff == TRUE){
if (pDevice->bHWRadioOff == TRUE) printk("chester bHWRadioOff\n");
if (pDevice->bRadioControlOff == TRUE) printk("chester bRadioControlOff\n");
        return FALSE;}

    if (pDevice->bRadioOff == FALSE)
       {
printk("chester pbRadioOff\n");
return TRUE;}

    BBvExitDeepSleep(pDevice->PortOffset, pDevice->byLocalID);

    MACvRegBitsOn(pDevice->PortOffset, MAC_REG_HOSTCR, HOSTCR_RXON);

    switch (pDevice->byRFType) {

        case RF_RFMD2959:
            MACvWordRegBitsOn(pDevice->PortOffset, MAC_REG_SOFTPWRCTL, SOFTPWRCTL_TXPEINV);
            MACvWordRegBitsOff(pDevice->PortOffset, MAC_REG_SOFTPWRCTL, SOFTPWRCTL_SWPE1);
            break;

        case RF_AIROHA:
        case RF_AL2230S:
        case RF_AIROHA7230: //RobertYu:20050104
            MACvWordRegBitsOn(pDevice->PortOffset, MAC_REG_SOFTPWRCTL, (SOFTPWRCTL_SWPE2 |
                                                                        SOFTPWRCTL_SWPE3));
            break;

    }

    pDevice->bRadioOff = FALSE;
//  2007-0409-03,<Add> by chester
printk("chester power on\n");
MACvRegBitsOff(pDevice->PortOffset, MAC_REG_GPIOCTL0, LED_ACTSET); //LED issue
    return bResult;
}