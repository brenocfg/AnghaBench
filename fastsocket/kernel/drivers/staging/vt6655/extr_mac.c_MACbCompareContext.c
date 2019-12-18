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
typedef  scalar_t__* PDWORD ;
typedef  scalar_t__ PBYTE ;
typedef  scalar_t__ DWORD_PTR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MAC_REG_AC0DMAPTR ; 
 scalar_t__ MAC_REG_RXDMAPTR0 ; 
 scalar_t__ MAC_REG_RXDMAPTR1 ; 
 scalar_t__ MAC_REG_TXDMAPTR0 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VNSvInPortD (scalar_t__,scalar_t__*) ; 

BOOL MACbCompareContext (DWORD_PTR dwIoBase, PBYTE pbyCxtBuf)
{
    DWORD       dwData;

    // compare MAC context to determine if this is a power lost init,
    // return TRUE for power remaining init, return FALSE for power lost init

    // compare CURR_RX_DESC_ADDR, CURR_TX_DESC_ADDR
    VNSvInPortD(dwIoBase + MAC_REG_TXDMAPTR0, &dwData);
    if (dwData != *(PDWORD)(pbyCxtBuf + MAC_REG_TXDMAPTR0)) {
        return FALSE;
    }

    VNSvInPortD(dwIoBase + MAC_REG_AC0DMAPTR, &dwData);
    if (dwData != *(PDWORD)(pbyCxtBuf + MAC_REG_AC0DMAPTR)) {
        return FALSE;
    }

    VNSvInPortD(dwIoBase + MAC_REG_RXDMAPTR0, &dwData);
    if (dwData != *(PDWORD)(pbyCxtBuf + MAC_REG_RXDMAPTR0)) {
        return FALSE;
    }

    VNSvInPortD(dwIoBase + MAC_REG_RXDMAPTR1, &dwData);
    if (dwData != *(PDWORD)(pbyCxtBuf + MAC_REG_RXDMAPTR1)) {
        return FALSE;
    }


    return TRUE;
}