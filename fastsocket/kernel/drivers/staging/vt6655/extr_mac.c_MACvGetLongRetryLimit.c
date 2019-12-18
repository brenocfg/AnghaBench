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
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 scalar_t__ MAC_REG_LRT ; 
 int /*<<< orphan*/  VNSvInPortB (scalar_t__,int /*<<< orphan*/ ) ; 

void MACvGetLongRetryLimit (DWORD_PTR dwIoBase, PBYTE pbyRetryLimit)
{
    // get LRT
    VNSvInPortB(dwIoBase + MAC_REG_LRT, pbyRetryLimit);
}