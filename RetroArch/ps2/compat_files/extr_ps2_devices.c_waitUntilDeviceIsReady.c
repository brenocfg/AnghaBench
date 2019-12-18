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
 int /*<<< orphan*/  fileXioDclose (int) ; 
 int fileXioDopen (char*) ; 
 int /*<<< orphan*/  nopdelay () ; 
 char* rootDevicePath (int) ; 

bool waitUntilDeviceIsReady(enum BootDeviceIDs device_id)
{
   int openFile = - 1;
   int retries = 3; /* just in case we tried a unit that is not working/connected */
   char *rootDevice = rootDevicePath(device_id);

   while(openFile < 0 && retries > 0)
   {
      openFile = fileXioDopen(rootDevice);
      /* Wait untill the device is ready */
      nopdelay();
      nopdelay();
      nopdelay();
      nopdelay();
      nopdelay();
      nopdelay();
      nopdelay();
      nopdelay();

      retries--;
   };
   if (openFile > 0) {
      fileXioDclose(openFile);
   }
   
   return openFile >= 0;
}