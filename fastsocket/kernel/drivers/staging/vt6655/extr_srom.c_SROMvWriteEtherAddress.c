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
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  SROMbWriteEmbedded (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ U_ETHER_ADDR_LEN ; 

void SROMvWriteEtherAddress (DWORD_PTR dwIoBase, PBYTE pbyEtherAddress)
{
    BYTE     ii;

    // ii = Rom Address
    for (ii = 0; ii < U_ETHER_ADDR_LEN; ii++) {
        SROMbWriteEmbedded(dwIoBase, ii, *pbyEtherAddress);
        pbyEtherAddress++;
    }
}