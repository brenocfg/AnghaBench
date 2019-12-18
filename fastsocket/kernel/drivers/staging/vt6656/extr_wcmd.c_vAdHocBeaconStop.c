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
struct TYPE_5__ {scalar_t__ eCurrMode; scalar_t__ eCurrState; scalar_t__ uIBSSChannel; scalar_t__ uScanChannel; } ;
struct TYPE_6__ {TYPE_1__ sMgmtObj; } ;
typedef  TYPE_1__* PSMgmtObject ;
typedef  TYPE_2__* PSDevice ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CB_MAX_CHANNEL_24G ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MAC_REG_TCR ; 
 int /*<<< orphan*/  MACvRegBitsOff (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCR_AUTOBCNTX ; 
 scalar_t__ TRUE ; 
 scalar_t__ WMAC_MODE_IBSS_STA ; 
 scalar_t__ WMAC_STATE_STARTED ; 

__attribute__((used)) static
void
vAdHocBeaconStop(PSDevice  pDevice)
{

    PSMgmtObject    pMgmt = &(pDevice->sMgmtObj);
    BOOL            bStop;

    /*
     * temporarily stop Beacon packet for AdHoc Server
     * if all of the following coditions are met:
     *  (1) STA is in AdHoc mode
     *  (2) VT3253 is programmed as automatic Beacon Transmitting
     *  (3) One of the following conditions is met
     *      (3.1) AdHoc channel is in B/G band and the
     *      current scan channel is in A band
     *      or
     *      (3.2) AdHoc channel is in A mode
     */
    bStop = FALSE;
    if ((pMgmt->eCurrMode == WMAC_MODE_IBSS_STA) &&
    (pMgmt->eCurrState >= WMAC_STATE_STARTED))
    {
        if ((pMgmt->uIBSSChannel <=  CB_MAX_CHANNEL_24G) &&
             (pMgmt->uScanChannel > CB_MAX_CHANNEL_24G))
        {
            bStop = TRUE;
        }
        if (pMgmt->uIBSSChannel >  CB_MAX_CHANNEL_24G)
        {
            bStop = TRUE;
        }
    }

    if (bStop)
    {
        //PMESG(("STOP_BEACON: IBSSChannel = %u, ScanChannel = %u\n",
        //        pMgmt->uIBSSChannel, pMgmt->uScanChannel));
        MACvRegBitsOff(pDevice, MAC_REG_TCR, TCR_AUTOBCNTX);
    }

}