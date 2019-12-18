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
typedef  int /*<<< orphan*/  PSDevice ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROLnsRequestOut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAC_REG_BSSID0 ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_MACREG ; 
 int /*<<< orphan*/  MESSAGE_TYPE_WRITE ; 

void MACvWriteBSSIDAddress(PSDevice pDevice, PBYTE pbyEtherAddr)
{
BYTE            pbyData[6];


    pbyData[0] = *((PBYTE)pbyEtherAddr);
    pbyData[1] = *((PBYTE)pbyEtherAddr+1);
    pbyData[2] = *((PBYTE)pbyEtherAddr+2);
    pbyData[3] = *((PBYTE)pbyEtherAddr+3);
    pbyData[4] = *((PBYTE)pbyEtherAddr+4);
    pbyData[5] = *((PBYTE)pbyEtherAddr+5);

    CONTROLnsRequestOut(pDevice,
                        MESSAGE_TYPE_WRITE,
                        MAC_REG_BSSID0,
                        MESSAGE_REQUEST_MACREG,
                        6,
                        pbyData
                        );
}