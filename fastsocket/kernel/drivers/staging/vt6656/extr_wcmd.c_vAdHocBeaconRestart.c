#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ eCurrMode; scalar_t__ eCurrState; } ;
struct TYPE_6__ {TYPE_1__ sMgmtObj; } ;
typedef  TYPE_1__* PSMgmtObject ;
typedef  TYPE_2__* PSDevice ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_REG_TCR ; 
 int /*<<< orphan*/  MACvRegBitsOn (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCR_AUTOBCNTX ; 
 scalar_t__ WMAC_MODE_IBSS_STA ; 
 scalar_t__ WMAC_STATE_STARTED ; 

__attribute__((used)) static
void
vAdHocBeaconRestart(PSDevice pDevice)
{
    PSMgmtObject    pMgmt = &(pDevice->sMgmtObj);

    /*
     * Restart Beacon packet for AdHoc Server
     * if all of the following coditions are met:
     *  (1) STA is in AdHoc mode
     *  (2) VT3253 is programmed as automatic Beacon Transmitting
     */
    if ((pMgmt->eCurrMode == WMAC_MODE_IBSS_STA) &&
    (pMgmt->eCurrState >= WMAC_STATE_STARTED))
    {
        //PMESG(("RESTART_BEACON\n"));
        MACvRegBitsOn(pDevice, MAC_REG_TCR, TCR_AUTOBCNTX);
    }

}