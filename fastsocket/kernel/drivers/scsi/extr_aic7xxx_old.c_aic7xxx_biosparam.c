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
struct scsi_device {TYPE_1__* host; } ;
struct block_device {int dummy; } ;
struct aic7xxx_host {int flags; } ;
typedef  int sector_t ;
struct TYPE_2__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int AHC_EXTEND_TRANS_A ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* scsi_bios_ptable (struct block_device*) ; 
 int scsi_partsize (unsigned char*,int,int*,int*,int*) ; 

__attribute__((used)) static int
aic7xxx_biosparam(struct scsi_device *sdev, struct block_device *bdev,
		sector_t capacity, int geom[])
{
  sector_t heads, sectors, cylinders;
  int ret;
  struct aic7xxx_host *p;
  unsigned char *buf;

  p = (struct aic7xxx_host *) sdev->host->hostdata;
  buf = scsi_bios_ptable(bdev);

  if ( buf )
  {
    ret = scsi_partsize(buf, capacity, &geom[2], &geom[0], &geom[1]);
    kfree(buf);
    if ( ret != -1 )
      return(ret);
  }
  
  heads = 64;
  sectors = 32;
  cylinders = capacity >> 11;

  if ((p->flags & AHC_EXTEND_TRANS_A) && (cylinders > 1024))
  {
    heads = 255;
    sectors = 63;
    cylinders = capacity >> 14;
    if(capacity > (65535 * heads * sectors))
      cylinders = 65535;
    else
      cylinders = ((unsigned int)capacity) / (unsigned int)(heads * sectors);
  }

  geom[0] = (int)heads;
  geom[1] = (int)sectors;
  geom[2] = (int)cylinders;

  return (0);
}