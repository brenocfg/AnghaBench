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
struct TYPE_3__ {int byBBCRc9; int byBBCR88; int byBBCR09; int byBBCR4d; scalar_t__ uConnectionRate; int /*<<< orphan*/  PortOffset; } ;
typedef  TYPE_1__* PSDevice ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  BBbReadEmbeded (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  BBbWriteEmbeded (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ RATE_11M ; 

void BBvLoopbackOff (PSDevice pDevice)
{
    BYTE      byData;
    DWORD_PTR dwIoBase = pDevice->PortOffset;

    BBbWriteEmbeded(dwIoBase, 0xC9, pDevice->byBBCRc9);//CR201
    BBbWriteEmbeded(dwIoBase, 0x88, pDevice->byBBCR88);//CR136
    BBbWriteEmbeded(dwIoBase, 0x09, pDevice->byBBCR09);//CR136
    BBbWriteEmbeded(dwIoBase, 0x4D, pDevice->byBBCR4d);//CR77

    if (pDevice->uConnectionRate <= RATE_11M) { // CCK
        // Set the CR33 Bit2 to disable internal Loopback.
        BBbReadEmbeded(dwIoBase, 0x21, &byData);//CR33
        BBbWriteEmbeded(dwIoBase, 0x21, (BYTE)(byData & 0xFE));//CR33
    }
    else { // OFDM
        BBbReadEmbeded(dwIoBase, 0x9A, &byData);//CR154
        BBbWriteEmbeded(dwIoBase, 0x9A, (BYTE)(byData & 0xFE));//CR154
    }
    BBbReadEmbeded(dwIoBase, 0x0E, &byData);//CR14
    BBbWriteEmbeded(dwIoBase, 0x0E, (BYTE)(byData | 0x80));//CR14

}