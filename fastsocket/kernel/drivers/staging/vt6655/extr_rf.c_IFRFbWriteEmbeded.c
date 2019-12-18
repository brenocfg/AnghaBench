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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IFREGCTL_DONE ; 
 scalar_t__ MAC_REG_IFREGCTL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VNSvInPortD (scalar_t__,int*) ; 
 int /*<<< orphan*/  VNSvOutPortD (scalar_t__,int) ; 
 scalar_t__ W_MAX_TIMEOUT ; 

BOOL IFRFbWriteEmbeded (DWORD_PTR dwIoBase, DWORD dwData)
{
    WORD    ww;
    DWORD   dwValue;

    VNSvOutPortD(dwIoBase + MAC_REG_IFREGCTL, dwData);

    // W_MAX_TIMEOUT is the timeout period
    for (ww = 0; ww < W_MAX_TIMEOUT; ww++) {
        VNSvInPortD(dwIoBase + MAC_REG_IFREGCTL, &dwValue);
        if (dwValue & IFREGCTL_DONE)
            break;
    }

    if (ww == W_MAX_TIMEOUT) {
//        DBG_PORT80_ALWAYS(0x32);
        return FALSE;
    }
    return TRUE;
}