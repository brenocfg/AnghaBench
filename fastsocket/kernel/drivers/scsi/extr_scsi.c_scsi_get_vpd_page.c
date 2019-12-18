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
 int EINVAL ; 
 int min (int,int) ; 
 int scsi_vpd_inquiry (struct scsi_device*,unsigned char*,unsigned char,int) ; 

int scsi_get_vpd_page(struct scsi_device *sdev, u8 page, unsigned char *buf,
		      int buf_len)
{
	int i, result;

	/* Ask for all the pages supported by this device */
	result = scsi_vpd_inquiry(sdev, buf, 0, buf_len);
	if (result)
		goto fail;

	/* If the user actually wanted this page, we can skip the rest */
	if (page == 0)
		return 0;

	for (i = 0; i < min((int)buf[3], buf_len - 4); i++)
		if (buf[i + 4] == page)
			goto found;

	if (i < buf[3] && i >= buf_len - 4)
		/* ran off the end of the buffer, give us benefit of doubt */
		goto found;
	/* The device claims it doesn't support the requested page */
	goto fail;

 found:
	result = scsi_vpd_inquiry(sdev, buf, page, buf_len);
	if (result)
		goto fail;

	return 0;

 fail:
	return -EINVAL;
}