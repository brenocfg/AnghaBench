#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bHWRadioOff; scalar_t__ bRadioControlOff; int byRFType; scalar_t__ bRadioOff; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSDevice ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BBvExitDeepSleep (TYPE_1__*) ; 
 scalar_t__ FALSE ; 
 int HOSTCR_RXON ; 
 int /*<<< orphan*/  MAC_REG_HOSTCR ; 
 int /*<<< orphan*/  MAC_REG_SOFTPWRCTL ; 
 int /*<<< orphan*/  MACvRegBitsOn (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
#define  RF_AIROHA7230 133 
#define  RF_AL2230 132 
#define  RF_AL2230S 131 
#define  RF_VT3226 130 
#define  RF_VT3226D0 129 
#define  RF_VT3342A0 128 
 int SOFTPWRCTL_SWPE2 ; 
 int SOFTPWRCTL_SWPE3 ; 
 scalar_t__ TRUE ; 

BOOL CARDbRadioPowerOn (PVOID pDeviceHandler)
{
PSDevice    pDevice = (PSDevice) pDeviceHandler;
BOOL bResult = TRUE;


    if ((pDevice->bHWRadioOff == TRUE) || (pDevice->bRadioControlOff == TRUE)) {
        return FALSE;
    }

    //if (pDevice->bRadioOff == FALSE)
    //    return TRUE;

    pDevice->bRadioOff = FALSE;

    BBvExitDeepSleep(pDevice);

    MACvRegBitsOn(pDevice, MAC_REG_HOSTCR, HOSTCR_RXON);

    switch (pDevice->byRFType) {
        case RF_AL2230:
        case RF_AL2230S:
        case RF_AIROHA7230:
        case RF_VT3226:     //RobertYu:20051111
        case RF_VT3226D0:
        case RF_VT3342A0:   //RobertYu:20060609
            MACvRegBitsOn(pDevice, MAC_REG_SOFTPWRCTL, (SOFTPWRCTL_SWPE2 | SOFTPWRCTL_SWPE3));
            break;
    }

    return bResult;
}