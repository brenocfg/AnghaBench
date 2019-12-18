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
struct TYPE_2__ {int error; scalar_t__ type; scalar_t__ length; } ;
struct pending_request {TYPE_1__ req; struct hpsb_packet* packet; } ;
struct hpsb_packet {int* header; int ack_code; } ;

/* Variables and functions */
#define  ACKX_ABORTED 131 
#define  ACKX_NONE 130 
#define  ACKX_SEND_ERROR 129 
#define  ACKX_TIMEOUT 128 
 int ACK_PENDING ; 
 int RAW1394_ERROR_ABORTED ; 
 int RAW1394_ERROR_SEND_ERROR ; 
 int RAW1394_ERROR_TIMEOUT ; 
 scalar_t__ RAW1394_REQ_ASYNC_READ ; 
 scalar_t__ RAW1394_REQ_ASYNC_STREAM ; 
 scalar_t__ RAW1394_REQ_ASYNC_WRITE ; 
 scalar_t__ RAW1394_REQ_LOCK ; 
 scalar_t__ RAW1394_REQ_LOCK64 ; 
 int RCODE_COMPLETE ; 
 int /*<<< orphan*/  hpsb_free_tlabel (struct hpsb_packet*) ; 
 int /*<<< orphan*/  queue_complete_req (struct pending_request*) ; 

__attribute__((used)) static void queue_complete_cb(struct pending_request *req)
{
	struct hpsb_packet *packet = req->packet;
	int rcode = (packet->header[1] >> 12) & 0xf;

	switch (packet->ack_code) {
	case ACKX_NONE:
	case ACKX_SEND_ERROR:
		req->req.error = RAW1394_ERROR_SEND_ERROR;
		break;
	case ACKX_ABORTED:
		req->req.error = RAW1394_ERROR_ABORTED;
		break;
	case ACKX_TIMEOUT:
		req->req.error = RAW1394_ERROR_TIMEOUT;
		break;
	default:
		req->req.error = (packet->ack_code << 16) | rcode;
		break;
	}

	if (!((packet->ack_code == ACK_PENDING) && (rcode == RCODE_COMPLETE))) {
		req->req.length = 0;
	}

	if ((req->req.type == RAW1394_REQ_ASYNC_READ) ||
	    (req->req.type == RAW1394_REQ_ASYNC_WRITE) ||
	    (req->req.type == RAW1394_REQ_ASYNC_STREAM) ||
	    (req->req.type == RAW1394_REQ_LOCK) ||
	    (req->req.type == RAW1394_REQ_LOCK64))
		hpsb_free_tlabel(packet);

	queue_complete_req(req);
}