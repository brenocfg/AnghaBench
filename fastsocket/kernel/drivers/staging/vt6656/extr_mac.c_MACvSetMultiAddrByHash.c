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
typedef  int /*<<< orphan*/  WORD ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  PSDevice ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROLnsRequestOut (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ MAC_REG_MAR0 ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_MACREG ; 
 int /*<<< orphan*/  MESSAGE_TYPE_WRITE_MASK ; 

void MACvSetMultiAddrByHash (PSDevice pDevice, BYTE byHashIdx)
{
    UINT            uByteIdx;
    BYTE            byBitMask;
    BYTE            pbyData[2];


    // calculate byte position
    uByteIdx = byHashIdx / 8;

    // calculate bit position
    byBitMask = 1;
    byBitMask <<= (byHashIdx % 8);
    // turn on the bit

    pbyData[0] = byBitMask;
    pbyData[1] = byBitMask;

    CONTROLnsRequestOut(pDevice,
                        MESSAGE_TYPE_WRITE_MASK,
                        (WORD) (MAC_REG_MAR0 + uByteIdx),
                        MESSAGE_REQUEST_MACREG,
                        2,
                        pbyData);
}