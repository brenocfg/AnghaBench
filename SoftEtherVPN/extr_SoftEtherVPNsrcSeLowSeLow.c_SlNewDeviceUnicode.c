#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  DriverObject; } ;
struct TYPE_16__ {int /*<<< orphan*/  Flags; scalar_t__ DeviceExtension; } ;
struct TYPE_15__ {int /*<<< orphan*/  OpenCloseLock; TYPE_1__* SymbolicLinkName; TYPE_1__* DeviceName; TYPE_3__* DeviceObject; } ;
struct TYPE_14__ {int /*<<< orphan*/  String; } ;
typedef  TYPE_1__ SL_UNICODE ;
typedef  TYPE_2__ SL_DEVICE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_3__ DEVICE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  DO_DEVICE_INITIALIZING ; 
 int /*<<< orphan*/  FILE_DEVICE_TRANSPORT ; 
 int /*<<< orphan*/  IoCreateDeviceSecure (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  IoCreateSymbolicLink (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IoDeleteDevice (TYPE_3__*) ; 
 scalar_t__ NG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlFreeUnicode (TYPE_1__*) ; 
 int /*<<< orphan*/  SlGetUnicode (TYPE_1__*) ; 
 int /*<<< orphan*/  SlNewLock () ; 
 TYPE_1__* SlNewUnicode (char*) ; 
 TYPE_2__* SlZeroMalloc (int) ; 
 TYPE_4__* sl ; 

SL_DEVICE *SlNewDeviceUnicode(SL_UNICODE *u_device_name, SL_UNICODE *u_sym_name)
{
	SL_DEVICE *ret = NULL;
	DEVICE_OBJECT *dev_obj = NULL;
	NTSTATUS r;
	SL_UNICODE *sddl;

	sddl = SlNewUnicode("D:P(A;;GA;;;SY)(A;;GA;;;BA)");

	/*r = IoCreateDevice(sl->DriverObject, sizeof(SL_DEVICE *),
		&u_device_name->String, FILE_DEVICE_TRANSPORT, 0, false, &dev_obj);*/

	r = IoCreateDeviceSecure(sl->DriverObject, sizeof(SL_DEVICE *),
		&u_device_name->String, FILE_DEVICE_TRANSPORT, 0, false, SlGetUnicode(sddl),
		NULL, &dev_obj);

	SlFreeUnicode(sddl);

	if (NG(r))
	{
		dev_obj = NULL;
		goto LABEL_CLEANUP;
	}

	r = IoCreateSymbolicLink(&u_sym_name->String, &u_device_name->String);
	if (NG(r))
	{
		// May fail due to a bug in Windows Kernel
	}

	ret = SlZeroMalloc(sizeof(SL_DEVICE));
	if (ret == NULL)
	{
		goto LABEL_CLEANUP;
	}

	ret->DeviceObject = dev_obj;
	ret->DeviceName = u_device_name;
	ret->SymbolicLinkName = u_sym_name;
	*((SL_DEVICE **)dev_obj->DeviceExtension) = ret;

	dev_obj->Flags &= ~DO_DEVICE_INITIALIZING;

	ret->OpenCloseLock = SlNewLock();

LABEL_CLEANUP:
	if (ret == NULL)
	{
		if (dev_obj != NULL)
		{
			IoDeleteDevice(dev_obj);
		}
	}

	return ret;
}