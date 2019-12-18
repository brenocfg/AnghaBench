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
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int RECEIVE_DIAGNOSTIC ; 
 int /*<<< orphan*/  SES_RETRIES ; 
 int /*<<< orphan*/  SES_TIMEOUT ; 
 int scsi_execute_req (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ses_recv_diag(struct scsi_device *sdev, int page_code,
			 void *buf, int bufflen)
{
	unsigned char cmd[] = {
		RECEIVE_DIAGNOSTIC,
		1,		/* Set PCV bit */
		page_code,
		bufflen >> 8,
		bufflen & 0xff,
		0
	};

	return scsi_execute_req(sdev, cmd, DMA_FROM_DEVICE, buf, bufflen,
				NULL, SES_TIMEOUT, SES_RETRIES, NULL);
}