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
typedef  scalar_t__ WORD ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PORT80 (int) ; 
 int DMACTL_RUN ; 
 scalar_t__ MAC_REG_RXDMACTL0 ; 
 scalar_t__ MAC_REG_RXDMAPTR0 ; 
 int /*<<< orphan*/  VNSvInPortB (scalar_t__,int*) ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int) ; 
 int /*<<< orphan*/  VNSvOutPortD (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ W_MAX_TIMEOUT ; 

void MACvSetCurrRx0DescAddr (DWORD_PTR dwIoBase, DWORD dwCurrDescAddr)
{
WORD    ww;
BYTE    byData;
BYTE    byOrgDMACtl;

    VNSvInPortB(dwIoBase + MAC_REG_RXDMACTL0, &byOrgDMACtl);
    if (byOrgDMACtl & DMACTL_RUN) {
        VNSvOutPortB(dwIoBase + MAC_REG_RXDMACTL0+2, DMACTL_RUN);
    }
    for (ww = 0; ww < W_MAX_TIMEOUT; ww++) {
        VNSvInPortB(dwIoBase + MAC_REG_RXDMACTL0, &byData);
        if ( !(byData & DMACTL_RUN))
            break;
    }
    if (ww == W_MAX_TIMEOUT) {
        DBG_PORT80(0x13);
    }
    VNSvOutPortD(dwIoBase + MAC_REG_RXDMAPTR0, dwCurrDescAddr);
    if (byOrgDMACtl & DMACTL_RUN) {
        VNSvOutPortB(dwIoBase + MAC_REG_RXDMACTL0, DMACTL_RUN);
    }
}