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
struct hpsb_packet {void (* complete_routine ) (void*) ;void* complete_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 

void hpsb_set_packet_complete_task(struct hpsb_packet *packet,
				   void (*routine)(void *), void *data)
{
	WARN_ON(packet->complete_routine != NULL);
	packet->complete_routine = routine;
	packet->complete_data = data;
	return;
}