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
typedef  scalar_t__ UINT ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ MAC_REG_MAR0 ; 
 int /*<<< orphan*/  MACvSelectPage0 (scalar_t__) ; 
 int /*<<< orphan*/  MACvSelectPage1 (scalar_t__) ; 
 int /*<<< orphan*/  VNSvInPortB (scalar_t__,int /*<<< orphan*/ *) ; 

BYTE MACbyReadMultiAddr (DWORD_PTR dwIoBase, UINT uByteIdx)
{
    BYTE byData;

    MACvSelectPage1(dwIoBase);
    VNSvInPortB(dwIoBase + MAC_REG_MAR0 + uByteIdx, &byData);
    MACvSelectPage0(dwIoBase);
    return byData;
}