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
struct scsi_disk {scalar_t__ lbpme; int lbpvpd; unsigned char lbpu; unsigned char lbpws; unsigned char lbpws10; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int const,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_get_vpd_page (int /*<<< orphan*/ ,int,unsigned char*,int const) ; 

__attribute__((used)) static void sd_read_block_provisioning(struct scsi_disk *sdkp)
{
	unsigned char *buffer;
	const int vpd_len = 8;

	if (sdkp->lbpme == 0)
		return;

	buffer = kmalloc(vpd_len, GFP_KERNEL);

	if (!buffer || scsi_get_vpd_page(sdkp->device, 0xb2, buffer, vpd_len))
		goto out;

	sdkp->lbpvpd	= 1;
	sdkp->lbpu	= (buffer[5] >> 7) & 1;	/* UNMAP */
	sdkp->lbpws	= (buffer[5] >> 6) & 1;	/* WRITE SAME(16) with UNMAP */
	sdkp->lbpws10	= (buffer[5] >> 5) & 1;	/* WRITE SAME(10) with UNMAP */

 out:
	kfree(buffer);
}