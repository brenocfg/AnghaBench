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
typedef  unsigned char u8 ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EIO ; 
 int HZ ; 
 unsigned char INQUIRY ; 
 int scsi_execute_req (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,unsigned char*,unsigned int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scsi_vpd_inquiry(struct scsi_device *sdev, unsigned char *buffer,
							u8 page, unsigned len)
{
	int result;
	unsigned char cmd[16];

	cmd[0] = INQUIRY;
	cmd[1] = 1;		/* EVPD */
	cmd[2] = page;
	cmd[3] = len >> 8;
	cmd[4] = len & 0xff;
	cmd[5] = 0;		/* Control byte */

	/*
	 * I'm not convinced we need to try quite this hard to get VPD, but
	 * all the existing users tried this hard.
	 */
	result = scsi_execute_req(sdev, cmd, DMA_FROM_DEVICE, buffer,
				  len, NULL, 30 * HZ, 3, NULL);
	if (result)
		return result;

	/* Sanity check that we got the page back that we asked for */
	if (buffer[1] != page)
		return -EIO;

	return 0;
}