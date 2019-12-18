#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WLAN_IE_MEASURE_REQ ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {scalar_t__ abyCurrentMSRReq; int /*<<< orphan*/  pAdapter; scalar_t__ uLengthOfRepEIDs; scalar_t__ abyCurrentMSRRep; int /*<<< orphan*/ * pCurrMeasureEIDRep; } ;
struct TYPE_8__ {int /*<<< orphan*/ * sMSRRepEIDs; } ;
struct TYPE_7__ {int /*<<< orphan*/  sMSRReqEIDs; } ;
typedef  TYPE_1__* PWLAN_FRAME_MSRREQ ;
typedef  TYPE_2__* PWLAN_FRAME_MSRREP ;
typedef  TYPE_3__* PSMgmtObject ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CARDbStartMeasure (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WLAN_A3FR_MAXLEN ; 
 int /*<<< orphan*/  WLAN_FRAME_MSRREQ ; 
 int /*<<< orphan*/  memcpy (scalar_t__,TYPE_1__*,scalar_t__) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sMSRReqEIDs ; 

__attribute__((used)) static BOOL s_bRxMSRReq(PSMgmtObject pMgmt, PWLAN_FRAME_MSRREQ pMSRReq, UINT uLength)
{
    size_t    uNumOfEIDs = 0;
    BOOL    bResult = TRUE;

    if (uLength <= WLAN_A3FR_MAXLEN) {
        memcpy(pMgmt->abyCurrentMSRReq, pMSRReq, uLength);
    }
    uNumOfEIDs = ((uLength - offsetof(WLAN_FRAME_MSRREQ, sMSRReqEIDs))/ (sizeof(WLAN_IE_MEASURE_REQ)));
    pMgmt->pCurrMeasureEIDRep = &(((PWLAN_FRAME_MSRREP) (pMgmt->abyCurrentMSRRep))->sMSRRepEIDs[0]);
    pMgmt->uLengthOfRepEIDs = 0;
    bResult = CARDbStartMeasure(pMgmt->pAdapter,
                                ((PWLAN_FRAME_MSRREQ) (pMgmt->abyCurrentMSRReq))->sMSRReqEIDs,
                                uNumOfEIDs
                                );
    return (bResult);
}