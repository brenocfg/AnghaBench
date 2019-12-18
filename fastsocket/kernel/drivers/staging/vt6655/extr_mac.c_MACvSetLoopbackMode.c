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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ MAC_REG_TEST ; 
 int /*<<< orphan*/  VNSvInPortB (scalar_t__,int*) ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int) ; 

void MACvSetLoopbackMode (DWORD_PTR dwIoBase, BYTE byLoopbackMode)
{
    BYTE byOrgValue;

    ASSERT(byLoopbackMode < 3);
    byLoopbackMode <<= 6;
    // set TCR
    VNSvInPortB(dwIoBase + MAC_REG_TEST, &byOrgValue);
    byOrgValue = byOrgValue & 0x3F;
    byOrgValue = byOrgValue | byLoopbackMode;
    VNSvOutPortB(dwIoBase + MAC_REG_TEST, byOrgValue);
}