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
struct scsi_device {int use_10_for_rw; int manage_start_stop; scalar_t__ type; int use_10_for_ms; int skip_ms_page_8; int fix_capacity; int start_stop_pwr_cond; int /*<<< orphan*/  request_queue; TYPE_1__* host; } ;
struct sbp2_lu {int workarounds; } ;
struct TYPE_2__ {scalar_t__* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBP2_MAX_SEG_SIZE ; 
 int SBP2_WORKAROUND_128K_MAX_TRANS ; 
 int SBP2_WORKAROUND_FIX_CAPACITY ; 
 int SBP2_WORKAROUND_MODE_SENSE_8 ; 
 int SBP2_WORKAROUND_POWER_CONDITION ; 
 scalar_t__ TYPE_DISK ; 
 scalar_t__ TYPE_ROM ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blk_queue_max_segment_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sbp2_exclusive_login ; 

__attribute__((used)) static int sbp2scsi_slave_configure(struct scsi_device *sdev)
{
	struct sbp2_lu *lu = (struct sbp2_lu *)sdev->host->hostdata[0];

	sdev->use_10_for_rw = 1;

	if (sbp2_exclusive_login)
		sdev->manage_start_stop = 1;
	if (sdev->type == TYPE_ROM)
		sdev->use_10_for_ms = 1;
	if (sdev->type == TYPE_DISK &&
	    lu->workarounds & SBP2_WORKAROUND_MODE_SENSE_8)
		sdev->skip_ms_page_8 = 1;
	if (lu->workarounds & SBP2_WORKAROUND_FIX_CAPACITY)
		sdev->fix_capacity = 1;
	if (lu->workarounds & SBP2_WORKAROUND_POWER_CONDITION)
		sdev->start_stop_pwr_cond = 1;
	if (lu->workarounds & SBP2_WORKAROUND_128K_MAX_TRANS)
		blk_queue_max_hw_sectors(sdev->request_queue, 128 * 1024 / 512);

	blk_queue_max_segment_size(sdev->request_queue, SBP2_MAX_SEG_SIZE);
	return 0;
}