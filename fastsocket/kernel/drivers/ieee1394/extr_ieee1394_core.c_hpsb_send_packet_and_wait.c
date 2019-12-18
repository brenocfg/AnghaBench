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
struct hpsb_packet {int dummy; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_packet ; 
 int hpsb_send_packet (struct hpsb_packet*) ; 
 int /*<<< orphan*/  hpsb_set_packet_complete_task (struct hpsb_packet*,int /*<<< orphan*/ ,struct completion*) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  wait_for_completion (struct completion*) ; 

int hpsb_send_packet_and_wait(struct hpsb_packet *packet)
{
	struct completion done;
	int retval;

	init_completion(&done);
	hpsb_set_packet_complete_task(packet, complete_packet, &done);
	retval = hpsb_send_packet(packet);
	if (retval == 0)
		wait_for_completion(&done);

	return retval;
}