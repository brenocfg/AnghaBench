#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int byBBCRc9; int byBBCR4d; int byBBCR88; scalar_t__ uConnectionRate; int byBBCR09; int /*<<< orphan*/  PortOffset; } ;
typedef  TYPE_1__* PSDevice ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  BBbReadEmbeded (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  BBbWriteEmbeded (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ RATE_11M ; 

void BBvLoopbackOn (PSDevice pDevice)
{
    BYTE      byData;
    DWORD_PTR dwIoBase = pDevice->PortOffset;

    //CR C9 = 0x00
    BBbReadEmbeded(dwIoBase, 0xC9, &pDevice->byBBCRc9);//CR201
    BBbWriteEmbeded(dwIoBase, 0xC9, 0);
    BBbReadEmbeded(dwIoBase, 0x4D, &pDevice->byBBCR4d);//CR77
    BBbWriteEmbeded(dwIoBase, 0x4D, 0x90);

    //CR 88 = 0x02(CCK), 0x03(OFDM)
    BBbReadEmbeded(dwIoBase, 0x88, &pDevice->byBBCR88);//CR136

    if (pDevice->uConnectionRate <= RATE_11M) { //CCK
        // Enable internal digital loopback: CR33 |= 0000 0001
        BBbReadEmbeded(dwIoBase, 0x21, &byData);//CR33
        BBbWriteEmbeded(dwIoBase, 0x21, (BYTE)(byData | 0x01));//CR33
        // CR154 = 0x00
        BBbWriteEmbeded(dwIoBase, 0x9A, 0);   //CR154

        BBbWriteEmbeded(dwIoBase, 0x88, 0x02);//CR239
    }
    else { //OFDM
        // Enable internal digital loopback:CR154 |= 0000 0001
        BBbReadEmbeded(dwIoBase, 0x9A, &byData);//CR154
        BBbWriteEmbeded(dwIoBase, 0x9A, (BYTE)(byData | 0x01));//CR154
        // CR33 = 0x00
        BBbWriteEmbeded(dwIoBase, 0x21, 0);   //CR33

        BBbWriteEmbeded(dwIoBase, 0x88, 0x03);//CR239
    }

    //CR14 = 0x00
    BBbWriteEmbeded(dwIoBase, 0x0E, 0);//CR14

    // Disable TX_IQUN
    BBbReadEmbeded(pDevice->PortOffset, 0x09, &pDevice->byBBCR09);
    BBbWriteEmbeded(pDevice->PortOffset, 0x09, (BYTE)(pDevice->byBBCR09 & 0xDE));
}