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
typedef  int WORD ;
typedef  int UINT ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 scalar_t__ MAC_REG_MISCFFCTL ; 
 scalar_t__ MAC_REG_MISCFFDATA ; 
 scalar_t__ MAC_REG_MISCFFNDEX ; 
 int MISCFFCTL_WRITE ; 
 int MISCFIFO_KEYENTRYSIZE ; 
 int MISCFIFO_KEYETRY0 ; 
 int /*<<< orphan*/  VNSvOutPortD (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VNSvOutPortW (scalar_t__,int) ; 

void MACvDisableKeyEntry (DWORD_PTR dwIoBase, UINT uEntryIdx)
{
WORD    wOffset;

    wOffset = MISCFIFO_KEYETRY0;
    wOffset += (uEntryIdx * MISCFIFO_KEYENTRYSIZE);

    VNSvOutPortW(dwIoBase + MAC_REG_MISCFFNDEX, wOffset);
    VNSvOutPortD(dwIoBase + MAC_REG_MISCFFDATA, 0);
    VNSvOutPortW(dwIoBase + MAC_REG_MISCFFCTL, MISCFFCTL_WRITE);
}