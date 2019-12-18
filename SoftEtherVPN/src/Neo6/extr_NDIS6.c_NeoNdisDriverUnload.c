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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PDRIVER_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  NdisMDeregisterMiniportDriver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndis_miniport_driver_handle ; 

VOID NeoNdisDriverUnload(PDRIVER_OBJECT DriverObject)
{
	NdisMDeregisterMiniportDriver(ndis_miniport_driver_handle);
}