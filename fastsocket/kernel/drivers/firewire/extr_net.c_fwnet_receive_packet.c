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
struct TYPE_2__ {unsigned long long offset; } ;
struct fwnet_device {TYPE_1__ handler; } ;
struct fw_request {int dummy; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int IEEE1394_ALL_NODES ; 
 int RCODE_ADDRESS_ERROR ; 
 int RCODE_COMPLETE ; 
 int RCODE_CONFLICT_ERROR ; 
 int RCODE_TYPE_ERROR ; 
 int TCODE_WRITE_BLOCK_REQUEST ; 
 int /*<<< orphan*/  fw_error (char*) ; 
 int /*<<< orphan*/  fw_send_response (struct fw_card*,struct fw_request*,int) ; 
 scalar_t__ fwnet_incoming_packet (struct fwnet_device*,void*,size_t,int,int,int) ; 
 int /*<<< orphan*/  kfree (struct fw_request*) ; 

__attribute__((used)) static void fwnet_receive_packet(struct fw_card *card, struct fw_request *r,
		int tcode, int destination, int source, int generation,
		int speed, unsigned long long offset, void *payload,
		size_t length, void *callback_data)
{
	struct fwnet_device *dev = callback_data;
	int rcode;

	if (destination == IEEE1394_ALL_NODES) {
		kfree(r);

		return;
	}

	if (offset != dev->handler.offset)
		rcode = RCODE_ADDRESS_ERROR;
	else if (tcode != TCODE_WRITE_BLOCK_REQUEST)
		rcode = RCODE_TYPE_ERROR;
	else if (fwnet_incoming_packet(dev, payload, length,
				       source, generation, false) != 0) {
		fw_error("Incoming packet failure\n");
		rcode = RCODE_CONFLICT_ERROR;
	} else
		rcode = RCODE_COMPLETE;

	fw_send_response(card, r, rcode);
}