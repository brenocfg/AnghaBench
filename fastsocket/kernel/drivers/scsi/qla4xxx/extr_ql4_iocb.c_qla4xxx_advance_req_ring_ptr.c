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
struct scsi_qla_host {int request_in; int /*<<< orphan*/  request_ptr; int /*<<< orphan*/  request_ring; } ;

/* Variables and functions */
 int REQUEST_QUEUE_DEPTH ; 

__attribute__((used)) static void qla4xxx_advance_req_ring_ptr(struct scsi_qla_host *ha)
{
	/* Advance request queue pointer */
	if (ha->request_in == (REQUEST_QUEUE_DEPTH - 1)) {
		ha->request_in = 0;
		ha->request_ptr = ha->request_ring;
	} else {
		ha->request_in++;
		ha->request_ptr++;
	}
}