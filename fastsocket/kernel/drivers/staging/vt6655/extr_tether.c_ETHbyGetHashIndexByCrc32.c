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
typedef  int /*<<< orphan*/  byTmpHash ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int BYTE ;

/* Variables and functions */
 int CRCdwCrc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  U_ETHER_ADDR_LEN ; 

BYTE ETHbyGetHashIndexByCrc32 (PBYTE pbyMultiAddr)
{
    int     ii;
    BYTE    byTmpHash;
    BYTE    byHash = 0;

    // get the least 6-bits from CRC generator
    byTmpHash = (BYTE)(CRCdwCrc32(pbyMultiAddr, U_ETHER_ADDR_LEN,
            0xFFFFFFFFL) & 0x3F);
    // reverse most bit to least bit
    for (ii = 0; ii < (sizeof(byTmpHash) * 8); ii++) {
        byHash <<= 1;
        if (byTmpHash & 0x01)
            byHash |= 1;
        byTmpHash >>= 1;
    }

    // adjust 6-bits to the right most
    return (byHash >> 2);
}