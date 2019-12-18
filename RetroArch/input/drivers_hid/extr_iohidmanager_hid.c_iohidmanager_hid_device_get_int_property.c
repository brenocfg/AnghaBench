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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  IOHIDDeviceRef ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  scalar_t__ CFNumberRef ;

/* Variables and functions */
 scalar_t__ CFGetTypeID (scalar_t__) ; 
 scalar_t__ CFNumberGetTypeID () ; 
 int /*<<< orphan*/  CFNumberGetValue (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IOHIDDeviceGetProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFNumberIntType ; 

__attribute__((used)) static int32_t iohidmanager_hid_device_get_int_property(
      IOHIDDeviceRef device, CFStringRef key)
{
   CFNumberRef ref = (CFNumberRef)IOHIDDeviceGetProperty(device, key);

   if (ref && (CFGetTypeID(ref) == CFNumberGetTypeID()))
   {
      int32_t value   = 0;
      CFNumberGetValue((CFNumberRef)ref, kCFNumberIntType, &value);
      return value;
   }

   return 0;
}