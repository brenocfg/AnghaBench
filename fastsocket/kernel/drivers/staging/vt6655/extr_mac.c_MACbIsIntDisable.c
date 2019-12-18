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
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MAC_REG_IMR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VNSvInPortD (scalar_t__,scalar_t__*) ; 

BOOL MACbIsIntDisable (DWORD_PTR dwIoBase)
{
    DWORD dwData;

    VNSvInPortD(dwIoBase + MAC_REG_IMR, &dwData);
    if (dwData != 0)
        return FALSE;

    return TRUE;
}