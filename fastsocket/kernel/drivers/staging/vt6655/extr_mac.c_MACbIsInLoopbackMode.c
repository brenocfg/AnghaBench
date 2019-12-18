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
typedef  scalar_t__ DWORD_PTR ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MAC_REG_TEST ; 
 int TEST_LBEXT ; 
 int TEST_LBINT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VNSvInPortB (scalar_t__,int*) ; 

BOOL MACbIsInLoopbackMode (DWORD_PTR dwIoBase)
{
    BYTE byOrgValue;

    VNSvInPortB(dwIoBase + MAC_REG_TEST, &byOrgValue);
    if (byOrgValue & (TEST_LBINT | TEST_LBEXT))
        return TRUE;
    return FALSE;
}