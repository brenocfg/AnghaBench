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
struct ipw_tx_packet {void (* packet_callback ) (void*,unsigned int) ;void* callback_data; } ;
struct ipw_hardware {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PRIO_DATA ; 
 int /*<<< orphan*/  TL_PROTOCOLID_COM_DATA ; 
 struct ipw_tx_packet* alloc_data_packet (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  send_packet (struct ipw_hardware*,int /*<<< orphan*/ ,struct ipw_tx_packet*) ; 

int ipwireless_send_packet(struct ipw_hardware *hw, unsigned int channel_idx,
			    const unsigned char *data, unsigned int length,
			    void (*callback) (void *cb, unsigned int length),
			    void *callback_data)
{
	struct ipw_tx_packet *packet;

	packet = alloc_data_packet(length, (channel_idx + 1),
			TL_PROTOCOLID_COM_DATA);
	if (!packet)
		return -ENOMEM;
	packet->packet_callback = callback;
	packet->callback_data = callback_data;
	memcpy((unsigned char *) packet + sizeof(struct ipw_tx_packet), data,
			length);

	send_packet(hw, PRIO_DATA, packet);
	return 0;
}