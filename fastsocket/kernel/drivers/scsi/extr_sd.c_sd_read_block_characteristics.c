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
typedef  int u16 ;
struct scsi_disk {TYPE_1__* disk; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int get_unaligned_be16 (unsigned char*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_flag_set_unlocked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_get_vpd_page (int /*<<< orphan*/ ,int,unsigned char*,int const) ; 

__attribute__((used)) static void sd_read_block_characteristics(struct scsi_disk *sdkp)
{
	unsigned char *buffer;
	u16 rot;
	const int vpd_len = 64;

	buffer = kmalloc(vpd_len, GFP_KERNEL);

	if (!buffer ||
	    /* Block Device Characteristics VPD */
	    scsi_get_vpd_page(sdkp->device, 0xb1, buffer, vpd_len))
		goto out;

	rot = get_unaligned_be16(&buffer[4]);

	if (rot == 1)
		queue_flag_set_unlocked(QUEUE_FLAG_NONROT, sdkp->disk->queue);

 out:
	kfree(buffer);
}