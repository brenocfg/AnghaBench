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
struct TYPE_4__ {int byRFType; void* bRadioOff; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSDevice ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BBvSetDeepSleep (TYPE_1__*) ; 
 int HOSTCR_RXON ; 
 int /*<<< orphan*/  MAC_REG_HOSTCR ; 
 int /*<<< orphan*/  MAC_REG_SOFTPWRCTL ; 
 int /*<<< orphan*/  MACvRegBitsOff (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
#define  RF_AIROHA7230 133 
#define  RF_AL2230 132 
#define  RF_AL2230S 131 
#define  RF_VT3226 130 
#define  RF_VT3226D0 129 
#define  RF_VT3342A0 128 
 int SOFTPWRCTL_SWPE2 ; 
 int SOFTPWRCTL_SWPE3 ; 
 void* TRUE ; 

BOOL CARDbRadioPowerOff (PVOID pDeviceHandler)
{
PSDevice    pDevice = (PSDevice) pDeviceHandler;
BOOL bResult = TRUE;

    //if (pDevice->bRadioOff == TRUE)
    //    return TRUE;

    pDevice->bRadioOff = TRUE;

    switch (pDevice->byRFType) {
        case RF_AL2230:
        case RF_AL2230S:
        case RF_AIROHA7230:
        case RF_VT3226:     //RobertYu:20051111
        case RF_VT3226D0:
        case RF_VT3342A0:   //RobertYu:20060609
            MACvRegBitsOff(pDevice, MAC_REG_SOFTPWRCTL, (SOFTPWRCTL_SWPE2 | SOFTPWRCTL_SWPE3));
            break;
    }

    MACvRegBitsOff(pDevice, MAC_REG_HOSTCR, HOSTCR_RXON);

    BBvSetDeepSleep(pDevice);

    return bResult;
}