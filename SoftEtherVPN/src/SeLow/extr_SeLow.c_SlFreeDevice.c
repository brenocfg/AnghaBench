#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  String; } ;
struct TYPE_5__ {int /*<<< orphan*/  OpenCloseLock; TYPE_2__* SymbolicLinkName; TYPE_2__* DeviceName; int /*<<< orphan*/  DeviceObject; } ;
typedef  TYPE_1__ SL_DEVICE ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  IoDeleteDevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoDeleteSymbolicLink (int /*<<< orphan*/ *) ; 
 scalar_t__ NG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlFree (TYPE_1__*) ; 
 int /*<<< orphan*/  SlFreeLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlFreeUnicode (TYPE_2__*) ; 

void SlFreeDevice(SL_DEVICE *dev)
{
	NTSTATUS r;
	// Validate arguments
	if (dev == NULL)
	{
		return;
	}

	r = IoDeleteSymbolicLink(&dev->SymbolicLinkName->String);
	if (NG(r))
	{
		// May fail due to a bug in Windows Kernel
	}

	IoDeleteDevice(dev->DeviceObject);

	SlFreeUnicode(dev->DeviceName);
	SlFreeUnicode(dev->SymbolicLinkName);

	SlFreeLock(dev->OpenCloseLock);

	SlFree(dev);
}