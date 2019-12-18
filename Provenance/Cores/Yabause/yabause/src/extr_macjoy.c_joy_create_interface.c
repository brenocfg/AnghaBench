#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  iface; } ;
typedef  TYPE_1__ joydata_t ;
typedef  int /*<<< orphan*/  io_object_t ;
struct TYPE_8__ {scalar_t__ (* QueryInterface ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Release ) (TYPE_2__**) ;} ;
typedef  int /*<<< orphan*/  SInt32 ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_2__ IOCFPlugInInterface ;

/* Variables and functions */
 int /*<<< orphan*/  CFUUIDGetUUIDBytes (int /*<<< orphan*/ ) ; 
 scalar_t__ IOCreatePlugInInterfaceForService (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__***,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  kIOCFPlugInInterfaceID ; 
 int /*<<< orphan*/  kIOHIDDeviceInterfaceID ; 
 int /*<<< orphan*/  kIOHIDDeviceUserClientTypeID ; 
 scalar_t__ kIOReturnSuccess ; 
 scalar_t__ stub1 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**) ; 

__attribute__((used)) static int joy_create_interface(io_object_t hidDevice, joydata_t *joy)  {
    IOCFPlugInInterface **plugin;
    SInt32 score = 0;

    /* Create the plugin that we will use to actually get the device interface
        that is needed. */
    if(IOCreatePlugInInterfaceForService(hidDevice,
                                         kIOHIDDeviceUserClientTypeID,
                                         kIOCFPlugInInterfaceID, &plugin,
                                         &score) != kIOReturnSuccess)   {
        return 0;
    }

    /* Grab the device interface from the plugin. */
    if((*plugin)->QueryInterface(plugin,
                                 CFUUIDGetUUIDBytes(kIOHIDDeviceInterfaceID),
                                 (LPVOID)&joy->iface) != S_OK)  {
        return 0;
    }

    /* The plugin has done all it needs to, release it. */
    (*plugin)->Release(plugin);

    return 1;
}