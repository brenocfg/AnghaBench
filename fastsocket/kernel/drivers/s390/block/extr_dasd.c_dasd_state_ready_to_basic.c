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
struct dasd_device {int /*<<< orphan*/  state; struct dasd_block* block; } ;
struct dasd_block {scalar_t__ s2b_shift; scalar_t__ bp_block; scalar_t__ blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_STATE_BASIC ; 
 int /*<<< orphan*/  DASD_STATE_READY ; 
 int /*<<< orphan*/  dasd_destroy_partitions (struct dasd_block*) ; 
 int dasd_flush_block_queue (struct dasd_block*) ; 
 int /*<<< orphan*/  dasd_flush_request_queue (struct dasd_block*) ; 

__attribute__((used)) static int dasd_state_ready_to_basic(struct dasd_device *device)
{
	int rc;

	device->state = DASD_STATE_BASIC;
	if (device->block) {
		struct dasd_block *block = device->block;
		rc = dasd_flush_block_queue(block);
		if (rc) {
			device->state = DASD_STATE_READY;
			return rc;
		}
		dasd_flush_request_queue(block);
		dasd_destroy_partitions(block);
		block->blocks = 0;
		block->bp_block = 0;
		block->s2b_shift = 0;
	}
	return 0;
}