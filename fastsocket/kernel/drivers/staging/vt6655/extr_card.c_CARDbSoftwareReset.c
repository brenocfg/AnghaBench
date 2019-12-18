#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  PortOffset; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PSDevice ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MACbSafeSoftwareReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL CARDbSoftwareReset (PVOID pDeviceHandler)
{
    PSDevice pDevice = (PSDevice) pDeviceHandler;

    // reset MAC
    if (!MACbSafeSoftwareReset(pDevice->PortOffset))
        return FALSE;

    return TRUE;
}