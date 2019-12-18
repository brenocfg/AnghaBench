#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ byRFType; scalar_t__ byBBType; int* abyBBVGA; int /*<<< orphan*/  byPacketType; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSDevice ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ BB_TYPE_11A ; 
 scalar_t__ BB_TYPE_11B ; 
 scalar_t__ BB_TYPE_11G ; 
 int /*<<< orphan*/  CARDbyGetPktType (TYPE_1__*) ; 
 int /*<<< orphan*/  CARDvSetRSPINF (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ControlvWriteByte (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MACvSetBBType (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_BBREG ; 
 scalar_t__ RF_AIROHA7230 ; 
 int /*<<< orphan*/  vUpdateIFS (TYPE_1__*) ; 

void CARDvSetBSSMode (PVOID pDeviceHandler)
{
    PSDevice    pDevice = (PSDevice) pDeviceHandler;
    // Set BB and packet type at the same time.//{{RobertYu:20050222, AL7230 have two TX PA output, only connet to b/g now
    // so in 11a mode need to set the MAC Reg0x4C to 11b/g mode to turn on PA
    if( (pDevice->byRFType == RF_AIROHA7230 ) && (pDevice->byBBType == BB_TYPE_11A) )
    {
        MACvSetBBType(pDevice, BB_TYPE_11G);
    }
    else
    {
        MACvSetBBType(pDevice, pDevice->byBBType);
    }
    pDevice->byPacketType = CARDbyGetPktType(pDevice);

    if (pDevice->byBBType == BB_TYPE_11A) {
        ControlvWriteByte(pDevice, MESSAGE_REQUEST_BBREG, 0x88, 0x03);
    } else if (pDevice->byBBType == BB_TYPE_11B) {
        ControlvWriteByte(pDevice, MESSAGE_REQUEST_BBREG, 0x88, 0x02);
    } else if (pDevice->byBBType == BB_TYPE_11G) {
        ControlvWriteByte(pDevice, MESSAGE_REQUEST_BBREG, 0x88, 0x08);
    }

    vUpdateIFS(pDevice);
    CARDvSetRSPINF(pDevice, (BYTE)pDevice->byBBType);

    if ( pDevice->byBBType == BB_TYPE_11A ) {
        //request by Jack 2005-04-26
        if (pDevice->byRFType == RF_AIROHA7230) {
            pDevice->abyBBVGA[0] = 0x20;
            ControlvWriteByte(pDevice, MESSAGE_REQUEST_BBREG, 0xE7, pDevice->abyBBVGA[0]);
        }
        pDevice->abyBBVGA[2] = 0x10;
        pDevice->abyBBVGA[3] = 0x10;
    } else {
        //request by Jack 2005-04-26
        if (pDevice->byRFType == RF_AIROHA7230) {
            pDevice->abyBBVGA[0] = 0x1C;
            ControlvWriteByte(pDevice, MESSAGE_REQUEST_BBREG, 0xE7, pDevice->abyBBVGA[0]);
        }
        pDevice->abyBBVGA[2] = 0x0;
        pDevice->abyBBVGA[3] = 0x0;
    }
}