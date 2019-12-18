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
struct scsi_device {int use_10_for_rw; int use_10_for_ms; int tagged_supported; int /*<<< orphan*/  request_queue; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  blk_queue_rq_timeout (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
stex_slave_config(struct scsi_device *sdev)
{
	sdev->use_10_for_rw = 1;
	sdev->use_10_for_ms = 1;
	blk_queue_rq_timeout(sdev->request_queue, 60 * HZ);
	sdev->tagged_supported = 1;

	return 0;
}