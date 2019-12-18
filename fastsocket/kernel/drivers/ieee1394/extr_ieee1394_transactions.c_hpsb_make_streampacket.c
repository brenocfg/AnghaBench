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
typedef  int /*<<< orphan*/  u8 ;
struct hpsb_packet {int node_id; scalar_t__* data; int /*<<< orphan*/  speed_code; struct hpsb_host* host; } ;
struct hpsb_host {int dummy; } ;

/* Variables and functions */
 int ALL_NODES ; 
 int /*<<< orphan*/  IEEE1394_SPEED_100 ; 
 int LOCAL_BUS ; 
 int /*<<< orphan*/  fill_async_stream_packet (struct hpsb_packet*,int,int,int,int) ; 
 struct hpsb_packet* hpsb_alloc_packet (int) ; 
 int /*<<< orphan*/  hpsb_free_packet (struct hpsb_packet*) ; 
 scalar_t__ hpsb_get_tlabel (struct hpsb_packet*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 

struct hpsb_packet *hpsb_make_streampacket(struct hpsb_host *host, u8 * buffer,
					   int length, int channel, int tag,
					   int sync)
{
	struct hpsb_packet *packet;

	if (length == 0)
		return NULL;

	packet = hpsb_alloc_packet(length);
	if (!packet)
		return NULL;

	if (length % 4) {	/* zero padding bytes */
		packet->data[length >> 2] = 0;
	}
	packet->host = host;

	/* Because it is too difficult to determine all PHY speeds and link
	 * speeds here, we use S100... */
	packet->speed_code = IEEE1394_SPEED_100;

	/* ...and prevent hpsb_send_packet() from overriding it. */
	packet->node_id = LOCAL_BUS | ALL_NODES;

	if (hpsb_get_tlabel(packet)) {
		hpsb_free_packet(packet);
		return NULL;
	}

	fill_async_stream_packet(packet, length, channel, tag, sync);
	if (buffer)
		memcpy(packet->data, buffer, length);

	return packet;
}