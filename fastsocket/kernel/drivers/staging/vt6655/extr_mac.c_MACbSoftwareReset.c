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
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HOSTCR_SOFTRST ; 
 scalar_t__ MAC_REG_HOSTCR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VNSvInPortB (scalar_t__,int*) ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int) ; 
 scalar_t__ W_MAX_TIMEOUT ; 

BOOL MACbSoftwareReset (DWORD_PTR dwIoBase)
{
    BYTE    byData;
    WORD    ww;

    // turn on HOSTCR_SOFTRST, just write 0x01 to reset
    //MACvRegBitsOn(dwIoBase, MAC_REG_HOSTCR, HOSTCR_SOFTRST);
    VNSvOutPortB(dwIoBase+ MAC_REG_HOSTCR, 0x01);

    for (ww = 0; ww < W_MAX_TIMEOUT; ww++) {
        VNSvInPortB(dwIoBase + MAC_REG_HOSTCR, &byData);
        if ( !(byData & HOSTCR_SOFTRST))
            break;
    }
    if (ww == W_MAX_TIMEOUT)
        return FALSE;
    return TRUE;

}