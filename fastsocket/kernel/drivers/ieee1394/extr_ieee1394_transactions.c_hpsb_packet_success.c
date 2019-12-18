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
struct hpsb_packet {int ack_code; int* header; int /*<<< orphan*/  tcode; int /*<<< orphan*/  node_id; } ;

/* Variables and functions */
#define  ACKX_ABORTED 146 
#define  ACKX_NONE 145 
#define  ACKX_SEND_ERROR 144 
#define  ACKX_TIMEOUT 143 
#define  ACK_ADDRESS_ERROR 142 
#define  ACK_BUSY_A 141 
#define  ACK_BUSY_B 140 
#define  ACK_BUSY_X 139 
#define  ACK_COMPLETE 138 
#define  ACK_CONFLICT_ERROR 137 
#define  ACK_DATA_ERROR 136 
#define  ACK_PENDING 135 
#define  ACK_TARDY 134 
#define  ACK_TYPE_ERROR 133 
 int EACCES ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  HPSB_ERR (char*,int,int /*<<< orphan*/ ,...) ; 
#define  RCODE_ADDRESS_ERROR 132 
#define  RCODE_COMPLETE 131 
#define  RCODE_CONFLICT_ERROR 130 
#define  RCODE_DATA_ERROR 129 
#define  RCODE_TYPE_ERROR 128 
 int /*<<< orphan*/  TCODE_LOCK_REQUEST ; 
 int /*<<< orphan*/  TCODE_WRITEB ; 
 int /*<<< orphan*/  TCODE_WRITEQ ; 

int hpsb_packet_success(struct hpsb_packet *packet)
{
	switch (packet->ack_code) {
	case ACK_PENDING:
		switch ((packet->header[1] >> 12) & 0xf) {
		case RCODE_COMPLETE:
			return 0;
		case RCODE_CONFLICT_ERROR:
			return -EAGAIN;
		case RCODE_DATA_ERROR:
			return -EREMOTEIO;
		case RCODE_TYPE_ERROR:
			return -EACCES;
		case RCODE_ADDRESS_ERROR:
			return -EINVAL;
		default:
			HPSB_ERR("received reserved rcode %d from node %d",
				 (packet->header[1] >> 12) & 0xf,
				 packet->node_id);
			return -EAGAIN;
		}

	case ACK_BUSY_X:
	case ACK_BUSY_A:
	case ACK_BUSY_B:
		return -EBUSY;

	case ACK_TYPE_ERROR:
		return -EACCES;

	case ACK_COMPLETE:
		if (packet->tcode == TCODE_WRITEQ
		    || packet->tcode == TCODE_WRITEB) {
			return 0;
		} else {
			HPSB_ERR("impossible ack_complete from node %d "
				 "(tcode %d)", packet->node_id, packet->tcode);
			return -EAGAIN;
		}

	case ACK_DATA_ERROR:
		if (packet->tcode == TCODE_WRITEB
		    || packet->tcode == TCODE_LOCK_REQUEST) {
			return -EAGAIN;
		} else {
			HPSB_ERR("impossible ack_data_error from node %d "
				 "(tcode %d)", packet->node_id, packet->tcode);
			return -EAGAIN;
		}

	case ACK_ADDRESS_ERROR:
		return -EINVAL;

	case ACK_TARDY:
	case ACK_CONFLICT_ERROR:
	case ACKX_NONE:
	case ACKX_SEND_ERROR:
	case ACKX_ABORTED:
	case ACKX_TIMEOUT:
		/* error while sending */
		return -EAGAIN;

	default:
		HPSB_ERR("got invalid ack %d from node %d (tcode %d)",
			 packet->ack_code, packet->node_id, packet->tcode);
		return -EAGAIN;
	}
}