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
typedef  int /*<<< orphan*/  IOHIDDeviceRef ;
typedef  scalar_t__ CFStringRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFStringGetCString (scalar_t__,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOHIDDeviceGetProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 int /*<<< orphan*/  kIOHIDProductKey ; 

__attribute__((used)) static void iohidmanager_hid_device_get_product_string(
      IOHIDDeviceRef device, char *buf, size_t len)
{
   CFStringRef ref = (CFStringRef)
      IOHIDDeviceGetProperty(device, CFSTR(kIOHIDProductKey));

   if (ref)
      CFStringGetCString(ref, buf, len, kCFStringEncodingUTF8);
}