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
struct adb_request {size_t* data; } ;

/* Variables and functions */
 struct adb_request* current_req ; 
 int data_index ; 
 int /*<<< orphan*/  data_len ; 
 scalar_t__ idle ; 
 int /*<<< orphan*/ ** pmu_data_len ; 
 scalar_t__ pmu_state ; 
 scalar_t__ req_awaiting_reply ; 
 int /*<<< orphan*/  send_byte (size_t) ; 
 scalar_t__ sending ; 
 int /*<<< orphan*/  wait_for_ack () ; 

__attribute__((used)) static void
pmu_start(void)
{
	struct adb_request *req;

	/* assert pmu_state == idle */
	/* get the packet to send */
	req = current_req;
	if (req == 0 || pmu_state != idle
	    || (/*req->reply_expected && */req_awaiting_reply))
		return;

	pmu_state = sending;
	data_index = 1;
	data_len = pmu_data_len[req->data[0]][0];

	/* Sounds safer to make sure ACK is high before writing. This helped
	 * kill a problem with ADB and some iBooks
	 */
	wait_for_ack();
	/* set the shift register to shift out and send a byte */
	send_byte(req->data[0]);
}