#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bus_reset_delay; int retry_delay; int async_data_setup_time; int req_ack_active_negation; int data_line_active_negation; int data_dma_burst_enable; int command_dma_burst_enable; int tag_aging; int selection_timeout; int max_queue_depth; scalar_t__ retry_count; int /*<<< orphan*/  initiator_scsi_id; } ;
struct qlogicpti {TYPE_2__* dev_param; scalar_t__ ultra; TYPE_1__ host_param; int /*<<< orphan*/  scsi_id; } ;
struct TYPE_4__ {int device_flags; int execution_throttle; int synchronous_period; int synchronous_offset; int device_enable; } ;

/* Variables and functions */
 int MAX_TARGETS ; 

__attribute__((used)) static inline void qlogicpti_set_hostdev_defaults(struct qlogicpti *qpti)
{
	int i;

	qpti->host_param.initiator_scsi_id = qpti->scsi_id;
	qpti->host_param.bus_reset_delay = 3;
	qpti->host_param.retry_count = 0;
	qpti->host_param.retry_delay = 5;
	qpti->host_param.async_data_setup_time = 3;
	qpti->host_param.req_ack_active_negation = 1;
	qpti->host_param.data_line_active_negation = 1;
	qpti->host_param.data_dma_burst_enable = 1;
	qpti->host_param.command_dma_burst_enable = 1;
	qpti->host_param.tag_aging = 8;
	qpti->host_param.selection_timeout = 250;
	qpti->host_param.max_queue_depth = 256;

	for(i = 0; i < MAX_TARGETS; i++) {
		/*
		 * disconnect, parity, arq, reneg on reset, and, oddly enough
		 * tags...the midlayer's notion of tagged support has to match
		 * our device settings, and since we base whether we enable a
		 * tag on a  per-cmnd basis upon what the midlayer sez, we
		 * actually enable the capability here.
		 */
		qpti->dev_param[i].device_flags = 0xcd;
		qpti->dev_param[i].execution_throttle = 16;
		if (qpti->ultra) {
			qpti->dev_param[i].synchronous_period = 12;
			qpti->dev_param[i].synchronous_offset = 8;
		} else {
			qpti->dev_param[i].synchronous_period = 25;
			qpti->dev_param[i].synchronous_offset = 12;
		}
		qpti->dev_param[i].device_enable = 1;
	}
}