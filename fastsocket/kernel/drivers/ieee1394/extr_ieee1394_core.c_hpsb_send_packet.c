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
typedef  int /*<<< orphan*/  u8 ;
struct hpsb_packet {scalar_t__ generation; scalar_t__ node_id; size_t data_size; size_t header_size; scalar_t__ type; int speed_code; int /*<<< orphan*/  header; scalar_t__ expect_response; int /*<<< orphan*/  data; int /*<<< orphan*/  queue; scalar_t__ sendtime; int /*<<< orphan*/  refcnt; scalar_t__ no_waiter; int /*<<< orphan*/  state; struct hpsb_host* host; } ;
struct hpsb_host {scalar_t__ node_id; int* speed; TYPE_1__* driver; int /*<<< orphan*/  pending_packets; scalar_t__ in_bus_reset; scalar_t__ is_shutdown; } ;
typedef  int /*<<< orphan*/  quadlet_t ;
struct TYPE_2__ {int (* transmit_packet ) (struct hpsb_host*,struct hpsb_packet*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_COMPLETE ; 
 int /*<<< orphan*/  ACK_PENDING ; 
 size_t ALL_NODES ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HPSB_ERR (char*) ; 
 int HZ ; 
 size_t NODEID_TO_NODE (scalar_t__) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_packet (char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ get_hpsb_generation (struct hpsb_host*) ; 
 scalar_t__ hpsb_async ; 
 int /*<<< orphan*/  hpsb_packet_received (struct hpsb_host*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsb_packet_sent (struct hpsb_host*,struct hpsb_packet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsb_queued ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pending_packets_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct hpsb_host*,struct hpsb_packet*) ; 

int hpsb_send_packet(struct hpsb_packet *packet)
{
	struct hpsb_host *host = packet->host;

	if (host->is_shutdown)
		return -EINVAL;
	if (host->in_bus_reset ||
	    (packet->generation != get_hpsb_generation(host)))
		return -EAGAIN;

	packet->state = hpsb_queued;

	/* This just seems silly to me */
	WARN_ON(packet->no_waiter && packet->expect_response);

	if (!packet->no_waiter || packet->expect_response) {
		unsigned long flags;

		atomic_inc(&packet->refcnt);
		/* Set the initial "sendtime" to 10 seconds from now, to
		   prevent premature expiry.  If a packet takes more than
		   10 seconds to hit the wire, we have bigger problems :) */
		packet->sendtime = jiffies + 10 * HZ;
		spin_lock_irqsave(&pending_packets_lock, flags);
		list_add_tail(&packet->queue, &host->pending_packets);
		spin_unlock_irqrestore(&pending_packets_lock, flags);
	}

	if (packet->node_id == host->node_id) {
		/* it is a local request, so handle it locally */

		quadlet_t *data;
		size_t size = packet->data_size + packet->header_size;

		data = kmalloc(size, GFP_ATOMIC);
		if (!data) {
			HPSB_ERR("unable to allocate memory for concatenating header and data");
			return -ENOMEM;
		}

		memcpy(data, packet->header, packet->header_size);

		if (packet->data_size)
			memcpy(((u8*)data) + packet->header_size, packet->data, packet->data_size);

		dump_packet("send packet local", packet->header, packet->header_size, -1);

		hpsb_packet_sent(host, packet, packet->expect_response ? ACK_PENDING : ACK_COMPLETE);
		hpsb_packet_received(host, data, size, 0);

		kfree(data);

		return 0;
	}

	if (packet->type == hpsb_async &&
	    NODEID_TO_NODE(packet->node_id) != ALL_NODES)
		packet->speed_code =
			host->speed[NODEID_TO_NODE(packet->node_id)];

	dump_packet("send packet", packet->header, packet->header_size, packet->speed_code);

	return host->driver->transmit_packet(host, packet);
}