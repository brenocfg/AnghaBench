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
typedef  int u64 ;
struct TYPE_2__ {int address; int type; int length; int misc; void* error; int /*<<< orphan*/  generation; int /*<<< orphan*/  sendb; } ;
struct pending_request {TYPE_1__ req; int /*<<< orphan*/  list; struct hpsb_packet* packet; int /*<<< orphan*/ * data; } ;
struct hpsb_packet {int /*<<< orphan*/  generation; int /*<<< orphan*/ * data; int /*<<< orphan*/ * header; } ;
struct file_info {int /*<<< orphan*/  reqlists_lock; int /*<<< orphan*/  req_pending; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGMSG (char*) ; 
 int ENOMEM ; 
 int EXTCODE_FETCH_ADD ; 
 int EXTCODE_LITTLE_ADD ; 
 void* RAW1394_ERROR_INVALID_ARG ; 
 void* RAW1394_ERROR_MEMFAULT ; 
 void* RAW1394_ERROR_SEND_ERROR ; 
 void* RAW1394_ERROR_STATE_ORDER ; 
#define  RAW1394_REQ_ASYNC_READ 132 
#define  RAW1394_REQ_ASYNC_STREAM 131 
#define  RAW1394_REQ_ASYNC_WRITE 130 
#define  RAW1394_REQ_LOCK 129 
#define  RAW1394_REQ_LOCK64 128 
 int /*<<< orphan*/  copy_from_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hpsb_free_tlabel (struct hpsb_packet*) ; 
 struct hpsb_packet* hpsb_make_lock64packet (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hpsb_packet* hpsb_make_lockpacket (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hpsb_packet* hpsb_make_readpacket (int /*<<< orphan*/ ,int,int,int) ; 
 struct hpsb_packet* hpsb_make_streampacket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int) ; 
 struct hpsb_packet* hpsb_make_writepacket (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ hpsb_send_packet (struct hpsb_packet*) ; 
 int /*<<< orphan*/  hpsb_set_packet_complete_task (struct hpsb_packet*,void (*) (void*),struct pending_request*) ; 
 int /*<<< orphan*/  int2ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ queue_complete_cb ; 
 int /*<<< orphan*/  queue_complete_req (struct pending_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int handle_async_request(struct file_info *fi,
				struct pending_request *req, int node)
{
	unsigned long flags;
	struct hpsb_packet *packet = NULL;
	u64 addr = req->req.address & 0xffffffffffffULL;

	switch (req->req.type) {
	case RAW1394_REQ_ASYNC_READ:
		DBGMSG("read_request called");
		packet =
		    hpsb_make_readpacket(fi->host, node, addr, req->req.length);

		if (!packet)
			return -ENOMEM;

		if (req->req.length == 4)
			req->data = &packet->header[3];
		else
			req->data = packet->data;

		break;

	case RAW1394_REQ_ASYNC_WRITE:
		DBGMSG("write_request called");

		packet = hpsb_make_writepacket(fi->host, node, addr, NULL,
					       req->req.length);
		if (!packet)
			return -ENOMEM;

		if (req->req.length == 4) {
			if (copy_from_user
			    (&packet->header[3], int2ptr(req->req.sendb),
			     req->req.length))
				req->req.error = RAW1394_ERROR_MEMFAULT;
		} else {
			if (copy_from_user
			    (packet->data, int2ptr(req->req.sendb),
			     req->req.length))
				req->req.error = RAW1394_ERROR_MEMFAULT;
		}

		req->req.length = 0;
		break;

	case RAW1394_REQ_ASYNC_STREAM:
		DBGMSG("stream_request called");

		packet =
		    hpsb_make_streampacket(fi->host, NULL, req->req.length,
					   node & 0x3f /*channel */ ,
					   (req->req.misc >> 16) & 0x3,
					   req->req.misc & 0xf);
		if (!packet)
			return -ENOMEM;

		if (copy_from_user(packet->data, int2ptr(req->req.sendb),
				   req->req.length))
			req->req.error = RAW1394_ERROR_MEMFAULT;

		req->req.length = 0;
		break;

	case RAW1394_REQ_LOCK:
		DBGMSG("lock_request called");
		if ((req->req.misc == EXTCODE_FETCH_ADD)
		    || (req->req.misc == EXTCODE_LITTLE_ADD)) {
			if (req->req.length != 4) {
				req->req.error = RAW1394_ERROR_INVALID_ARG;
				break;
			}
		} else {
			if (req->req.length != 8) {
				req->req.error = RAW1394_ERROR_INVALID_ARG;
				break;
			}
		}

		packet = hpsb_make_lockpacket(fi->host, node, addr,
					      req->req.misc, NULL, 0);
		if (!packet)
			return -ENOMEM;

		if (copy_from_user(packet->data, int2ptr(req->req.sendb),
				   req->req.length)) {
			req->req.error = RAW1394_ERROR_MEMFAULT;
			break;
		}

		req->data = packet->data;
		req->req.length = 4;
		break;

	case RAW1394_REQ_LOCK64:
		DBGMSG("lock64_request called");
		if ((req->req.misc == EXTCODE_FETCH_ADD)
		    || (req->req.misc == EXTCODE_LITTLE_ADD)) {
			if (req->req.length != 8) {
				req->req.error = RAW1394_ERROR_INVALID_ARG;
				break;
			}
		} else {
			if (req->req.length != 16) {
				req->req.error = RAW1394_ERROR_INVALID_ARG;
				break;
			}
		}
		packet = hpsb_make_lock64packet(fi->host, node, addr,
						req->req.misc, NULL, 0);
		if (!packet)
			return -ENOMEM;

		if (copy_from_user(packet->data, int2ptr(req->req.sendb),
				   req->req.length)) {
			req->req.error = RAW1394_ERROR_MEMFAULT;
			break;
		}

		req->data = packet->data;
		req->req.length = 8;
		break;

	default:
		req->req.error = RAW1394_ERROR_STATE_ORDER;
	}

	req->packet = packet;

	if (req->req.error) {
		req->req.length = 0;
		queue_complete_req(req);
		return 0;
	}

	hpsb_set_packet_complete_task(packet,
				      (void (*)(void *))queue_complete_cb, req);

	spin_lock_irqsave(&fi->reqlists_lock, flags);
	list_add_tail(&req->list, &fi->req_pending);
	spin_unlock_irqrestore(&fi->reqlists_lock, flags);

	packet->generation = req->req.generation;

	if (hpsb_send_packet(packet) < 0) {
		req->req.error = RAW1394_ERROR_SEND_ERROR;
		req->req.length = 0;
		hpsb_free_tlabel(packet);
		queue_complete_req(req);
	}
	return 0;
}