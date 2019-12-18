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
typedef  int UINT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int MACbyReadMultiAddr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MACvWriteMultiAddr (int /*<<< orphan*/ ,int,int) ; 

void MACvResetMultiAddrByHash (DWORD_PTR dwIoBase, BYTE byHashIdx)
{
    UINT uByteIdx;
    BYTE byBitMask;
    BYTE byOrgValue;

    // calculate byte position
    uByteIdx = byHashIdx / 8;
    ASSERT(uByteIdx < 8);
    // calculate bit position
    byBitMask = 1;
    byBitMask <<= (byHashIdx % 8);
    // turn off the bit
    byOrgValue = MACbyReadMultiAddr(dwIoBase, uByteIdx);
    MACvWriteMultiAddr(dwIoBase, uByteIdx, (BYTE)(byOrgValue & (~byBitMask)));
}