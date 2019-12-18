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
typedef  int u8 ;
struct scsi_device {int sector_size; } ;

/* Variables and functions */

__attribute__((used)) static u8 scu_bg_blk_size(struct scsi_device *sdp)
{
	switch (sdp->sector_size) {
	case 512:
		return 0;
	case 1024:
		return 1;
	case 4096:
		return 3;
	default:
		return 0xff;
	}
}