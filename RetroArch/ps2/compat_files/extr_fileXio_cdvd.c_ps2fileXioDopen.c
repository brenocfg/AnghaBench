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
typedef  enum BootDeviceIDs { ____Placeholder_BootDeviceIDs } BootDeviceIDs ;

/* Variables and functions */
 int BOOT_DEVICE_CDFS ; 
 int fileXioCDDopen (char const*) ; 
 int fileXioDopen (char const*) ; 
 int getBootDeviceID (char*) ; 

int ps2fileXioDopen(const char *name)
{
   enum BootDeviceIDs deviceID = getBootDeviceID((char *)name);
   int fd = -1;
   if (deviceID == BOOT_DEVICE_CDFS) {
      fd = fileXioCDDopen(name);
   } else {
      fd = fileXioDopen(name);
   }

   return fd;
}