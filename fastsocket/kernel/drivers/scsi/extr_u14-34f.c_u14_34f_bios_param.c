#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {int dummy; } ;
struct block_device {int dummy; } ;
typedef  unsigned int sector_t ;
struct TYPE_2__ {int heads; int sectors; } ;

/* Variables and functions */
 int FALSE ; 
 TYPE_1__* HD (unsigned int) ; 
 int /*<<< orphan*/  driver_name ; 
 scalar_t__ ext_tran ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ scsicam_bios_param (struct block_device*,unsigned int,int*) ; 

__attribute__((used)) static int u14_34f_bios_param(struct scsi_device *disk,
                 struct block_device *bdev, sector_t capacity, int *dkinfo) {
   unsigned int j = 0;
   unsigned int size = capacity;

   dkinfo[0] = HD(j)->heads;
   dkinfo[1] = HD(j)->sectors;
   dkinfo[2] = size / (HD(j)->heads * HD(j)->sectors);

   if (ext_tran && (scsicam_bios_param(bdev, capacity, dkinfo) < 0)) {
      dkinfo[0] = 255;
      dkinfo[1] = 63;
      dkinfo[2] = size / (dkinfo[0] * dkinfo[1]);
      }

#if defined (DEBUG_GEOMETRY)
   printk ("%s: bios_param, head=%d, sec=%d, cyl=%d.\n", driver_name,
           dkinfo[0], dkinfo[1], dkinfo[2]);
#endif

   return FALSE;
}