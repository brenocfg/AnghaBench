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
typedef  int /*<<< orphan*/  u64 ;
struct hpsb_packet {unsigned int generation; } ;
struct hpsb_host {int dummy; } ;
typedef  int /*<<< orphan*/  quadlet_t ;
typedef  int /*<<< orphan*/  nodeid_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  hpsb_free_packet (struct hpsb_packet*) ; 
 int /*<<< orphan*/  hpsb_free_tlabel (struct hpsb_packet*) ; 
 struct hpsb_packet* hpsb_make_writepacket (struct hpsb_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int hpsb_packet_success (struct hpsb_packet*) ; 
 int hpsb_send_packet_and_wait (struct hpsb_packet*) ; 

int hpsb_write(struct hpsb_host *host, nodeid_t node, unsigned int generation,
	       u64 addr, quadlet_t * buffer, size_t length)
{
	struct hpsb_packet *packet;
	int retval;

	if (length == 0)
		return -EINVAL;

	packet = hpsb_make_writepacket(host, node, addr, buffer, length);

	if (!packet)
		return -ENOMEM;

	packet->generation = generation;
	retval = hpsb_send_packet_and_wait(packet);
	if (retval < 0)
		goto hpsb_write_fail;

	retval = hpsb_packet_success(packet);

      hpsb_write_fail:
	hpsb_free_tlabel(packet);
	hpsb_free_packet(packet);

	return retval;
}