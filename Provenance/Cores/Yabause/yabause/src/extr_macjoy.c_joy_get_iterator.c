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
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  io_iterator_t ;
typedef  scalar_t__ IOReturn ;
typedef  int /*<<< orphan*/  CFMutableDictionaryRef ;

/* Variables and functions */
 scalar_t__ IOServiceGetMatchingServices (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOServiceMatching (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kIOHIDDeviceKey ; 
 scalar_t__ kIOReturnSuccess ; 

__attribute__((used)) static void joy_get_iterator(mach_port_t port, io_iterator_t *iter) {
    CFMutableDictionaryRef d;
    IOReturn rv;

    /* Create a matching dictionary that will be used to search the device
        tree. */
    if(!(d = IOServiceMatching(kIOHIDDeviceKey)))  {
        return;
    }

    /* Get all matching devices from IOKit. */
    rv = IOServiceGetMatchingServices(port, d, iter);

    if(rv != kIOReturnSuccess || !(*iter))  {
        return;
    }
}