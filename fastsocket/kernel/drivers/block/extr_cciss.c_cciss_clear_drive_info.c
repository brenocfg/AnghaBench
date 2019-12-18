#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int raid_level; int /*<<< orphan*/  vendor; int /*<<< orphan*/  rev; int /*<<< orphan*/  model; int /*<<< orphan*/  serial_no; scalar_t__ cylinders; scalar_t__ sectors; scalar_t__ heads; scalar_t__ block_size; scalar_t__ nr_blocks; } ;
typedef  TYPE_1__ drive_info_struct ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cciss_clear_drive_info(drive_info_struct *drive_info)
{
	/* zero out the disk size info */
	drive_info->nr_blocks = 0;
	drive_info->block_size = 0;
	drive_info->heads = 0;
	drive_info->sectors = 0;
	drive_info->cylinders = 0;
	drive_info->raid_level = -1;
	memset(drive_info->serial_no, 0, sizeof(drive_info->serial_no));
	memset(drive_info->model, 0, sizeof(drive_info->model));
	memset(drive_info->rev, 0, sizeof(drive_info->rev));
	memset(drive_info->vendor, 0, sizeof(drive_info->vendor));
	/*
	 * don't clear the LUNID though, we need to remember which
	 * one this one is.
	 */
}