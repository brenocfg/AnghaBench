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
struct scsi_device {int /*<<< orphan*/  request_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_BOUNCE_ANY ; 
 int HZ ; 
 int /*<<< orphan*/  MSG_SIMPLE_TAG ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  STORVSC_MAX_IO_REQUESTS ; 
 int /*<<< orphan*/  blk_queue_bounce_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_segment_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_rq_timeout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_adjust_queue_depth (struct scsi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int storvsc_timeout ; 

__attribute__((used)) static int storvsc_device_configure(struct scsi_device *sdevice)
{
	scsi_adjust_queue_depth(sdevice, MSG_SIMPLE_TAG,
				STORVSC_MAX_IO_REQUESTS);

	blk_queue_max_segment_size(sdevice->request_queue, PAGE_SIZE);

	blk_queue_bounce_limit(sdevice->request_queue, BLK_BOUNCE_ANY);

	blk_queue_rq_timeout(sdevice->request_queue, (storvsc_timeout * HZ));

	return 0;
}