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
typedef  scalar_t__ uint16_t ;
struct scsi_qla_host {scalar_t__ response_ptr; } ;
struct response {int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESPONSE_PROCESSED ; 
 scalar_t__ RESPONSE_QUEUE_DEPTH ; 

__attribute__((used)) static void qla4xxx_init_response_q_entries(struct scsi_qla_host *ha)
{
	uint16_t cnt;
	struct response *pkt;

	pkt = (struct response *)ha->response_ptr;
	for (cnt = 0; cnt < RESPONSE_QUEUE_DEPTH; cnt++) {
		pkt->signature = RESPONSE_PROCESSED;
		pkt++;
	}
}