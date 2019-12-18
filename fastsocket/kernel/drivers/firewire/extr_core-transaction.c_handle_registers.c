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
struct fw_request {int dummy; } ;
struct fw_card {unsigned long long broadcast_channel; TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {unsigned long long (* get_bus_time ) (struct fw_card*) ;} ;

/* Variables and functions */
 int BROADCAST_CHANNEL_INITIAL ; 
 int BROADCAST_CHANNEL_VALID ; 
 int /*<<< orphan*/  BUG () ; 
#define  CSR_BANDWIDTH_AVAILABLE 135 
#define  CSR_BROADCAST_CHANNEL 134 
#define  CSR_BUSY_TIMEOUT 133 
#define  CSR_BUS_MANAGER_ID 132 
#define  CSR_BUS_TIME 131 
#define  CSR_CHANNELS_AVAILABLE_HI 130 
#define  CSR_CHANNELS_AVAILABLE_LO 129 
#define  CSR_CYCLE_TIME 128 
 unsigned long long CSR_REGISTER_BASE ; 
 int RCODE_ADDRESS_ERROR ; 
 int RCODE_COMPLETE ; 
 int RCODE_TYPE_ERROR ; 
 int /*<<< orphan*/  TCODE_IS_READ_REQUEST (int) ; 
 int TCODE_READ_QUADLET_REQUEST ; 
 int TCODE_WRITE_QUADLET_REQUEST ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned long long) ; 
 int /*<<< orphan*/  fw_send_response (struct fw_card*,struct fw_request*,int) ; 
 unsigned long long stub1 (struct fw_card*) ; 

__attribute__((used)) static void handle_registers(struct fw_card *card, struct fw_request *request,
		int tcode, int destination, int source, int generation,
		int speed, unsigned long long offset,
		void *payload, size_t length, void *callback_data)
{
	int reg = offset & ~CSR_REGISTER_BASE;
	unsigned long long bus_time;
	__be32 *data = payload;
	int rcode = RCODE_COMPLETE;

	switch (reg) {
	case CSR_CYCLE_TIME:
	case CSR_BUS_TIME:
		if (!TCODE_IS_READ_REQUEST(tcode) || length != 4) {
			rcode = RCODE_TYPE_ERROR;
			break;
		}

		bus_time = card->driver->get_bus_time(card);
		if (reg == CSR_CYCLE_TIME)
			*data = cpu_to_be32(bus_time);
		else
			*data = cpu_to_be32(bus_time >> 25);
		break;

	case CSR_BROADCAST_CHANNEL:
		if (tcode == TCODE_READ_QUADLET_REQUEST)
			*data = cpu_to_be32(card->broadcast_channel);
		else if (tcode == TCODE_WRITE_QUADLET_REQUEST)
			card->broadcast_channel =
			    (be32_to_cpu(*data) & BROADCAST_CHANNEL_VALID) |
			    BROADCAST_CHANNEL_INITIAL;
		else
			rcode = RCODE_TYPE_ERROR;
		break;

	case CSR_BUS_MANAGER_ID:
	case CSR_BANDWIDTH_AVAILABLE:
	case CSR_CHANNELS_AVAILABLE_HI:
	case CSR_CHANNELS_AVAILABLE_LO:
		/*
		 * FIXME: these are handled by the OHCI hardware and
		 * the stack never sees these request. If we add
		 * support for a new type of controller that doesn't
		 * handle this in hardware we need to deal with these
		 * transactions.
		 */
		BUG();
		break;

	case CSR_BUSY_TIMEOUT:
		/* FIXME: Implement this. */

	default:
		rcode = RCODE_ADDRESS_ERROR;
		break;
	}

	fw_send_response(card, request, rcode);
}