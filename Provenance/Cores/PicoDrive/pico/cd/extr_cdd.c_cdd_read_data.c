#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {TYPE_2__* tracks; } ;
struct TYPE_6__ {int lba; int sectorSize; TYPE_1__ toc; } ;
struct TYPE_5__ {int end; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_3__ cdd ; 
 int /*<<< orphan*/  pm_read (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void cdd_read_data(uint8 *dst)
{
  /* only read DATA track sectors */
  if ((cdd.lba >= 0) && (cdd.lba < cdd.toc.tracks[0].end))
  {
    /* BIN format ? */
    if (cdd.sectorSize == 2352)
    {
      /* skip 16-byte header */
      pm_seek(cdd.toc.tracks[0].fd, cdd.lba * 2352 + 16, SEEK_SET);
    }

    /* read sector data (Mode 1 = 2048 bytes) */
    pm_read(dst, 2048, cdd.toc.tracks[0].fd);
  }
}