#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int id; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ deviceinfo_struct ;
struct TYPE_5__ {int cartid; } ;

/* Variables and functions */
 TYPE_2__* CartridgeArea ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,...) ; 

deviceinfo_struct *BupGetDeviceList(int *numdevices)
{
   deviceinfo_struct *device;
   int devicecount=1;

   if ((CartridgeArea->cartid & 0xF0) == 0x20)
      devicecount++;

   if ((device = (deviceinfo_struct *)malloc(devicecount * sizeof(deviceinfo_struct))) == NULL)
   {
      *numdevices = 0;
      return NULL;
   }

   *numdevices = devicecount;

   device[0].id = 0;
   sprintf(device[0].name, "Internal Backup RAM");

   if ((CartridgeArea->cartid & 0xF0) == 0x20)
   {
      device[1].id = 1;
      sprintf(device[1].name, "%d Mbit Backup RAM Cartridge", 1 << ((CartridgeArea->cartid & 0xF)+1));  
   }

   // For now it's only internal backup ram and cartridge, no floppy :(
//   device[2].id = 2;
//   sprintf(device[1].name, "Floppy Disk Drive");

   return device;
}