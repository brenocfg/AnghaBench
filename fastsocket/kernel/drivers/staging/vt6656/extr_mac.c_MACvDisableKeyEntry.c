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
typedef  int WORD ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  PSDevice ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROLnsRequestOut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  MESSAGE_TYPE_CLRKEYENTRY ; 
 int MISCFIFO_KEYENTRYSIZE ; 
 int MISCFIFO_KEYETRY0 ; 

void MACvDisableKeyEntry (PSDevice pDevice, UINT uEntryIdx)
{
WORD    wOffset;
BYTE            byData;


    byData = (BYTE) uEntryIdx;

    wOffset = MISCFIFO_KEYETRY0;
    wOffset += (uEntryIdx * MISCFIFO_KEYENTRYSIZE);

    //VNSvOutPortW(dwIoBase + MAC_REG_MISCFFNDEX, wOffset);
    //VNSvOutPortD(dwIoBase + MAC_REG_MISCFFDATA, 0);
    //VNSvOutPortW(dwIoBase + MAC_REG_MISCFFCTL, MISCFFCTL_WRITE);

    //issue write misc fifo command to device
    CONTROLnsRequestOut(pDevice,
                        MESSAGE_TYPE_CLRKEYENTRY,
                        0,
                        0,
                        1,
                        &byData
                        );
}