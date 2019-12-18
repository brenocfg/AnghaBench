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
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAC_LB_INTERNAL ; 
 int /*<<< orphan*/  MAC_LB_NONE ; 
 int /*<<< orphan*/  MACbSafeStop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvIntDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvSetLoopbackMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL MACbShutdown (DWORD_PTR dwIoBase)
{
    // disable MAC IMR
    MACvIntDisable(dwIoBase);
    MACvSetLoopbackMode(dwIoBase, MAC_LB_INTERNAL);
    // stop the adapter
    if (!MACbSafeStop(dwIoBase)) {
        MACvSetLoopbackMode(dwIoBase, MAC_LB_NONE);
        return FALSE;
    }
    MACvSetLoopbackMode(dwIoBase, MAC_LB_NONE);
    return TRUE;
}