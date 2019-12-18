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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ length; int /*<<< orphan*/  error; int /*<<< orphan*/  generation; scalar_t__ sendb; } ;
struct pending_request {TYPE_1__ req; int /*<<< orphan*/  list; struct hpsb_packet* packet; } ;
struct hpsb_packet {int /*<<< orphan*/  generation; } ;
struct file_info {int /*<<< orphan*/  reqlists_lock; int /*<<< orphan*/  req_pending; int /*<<< orphan*/  host; } ;
typedef  int quadlet_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBGMSG (char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RAW1394_ERROR_SEND_ERROR ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct hpsb_packet* hpsb_make_phypacket (int /*<<< orphan*/ ,int) ; 
 int hpsb_send_packet (struct hpsb_packet*) ; 
 int /*<<< orphan*/  hpsb_set_packet_complete_task (struct hpsb_packet*,void (*) (void*),struct pending_request*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ queue_complete_cb ; 
 int /*<<< orphan*/  queue_complete_req (struct pending_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int write_phypacket(struct file_info *fi, struct pending_request *req)
{
	struct hpsb_packet *packet = NULL;
	int retval = 0;
	quadlet_t data;
	unsigned long flags;

	data = be32_to_cpu((u32) req->req.sendb);
	DBGMSG("write_phypacket called - quadlet 0x%8.8x ", data);
	packet = hpsb_make_phypacket(fi->host, data);
	if (!packet)
		return -ENOMEM;
	req->req.length = 0;
	req->packet = packet;
	hpsb_set_packet_complete_task(packet,
				      (void (*)(void *))queue_complete_cb, req);
	spin_lock_irqsave(&fi->reqlists_lock, flags);
	list_add_tail(&req->list, &fi->req_pending);
	spin_unlock_irqrestore(&fi->reqlists_lock, flags);
	packet->generation = req->req.generation;
	retval = hpsb_send_packet(packet);
	DBGMSG("write_phypacket send_packet called => retval: %d ", retval);
	if (retval < 0) {
		req->req.error = RAW1394_ERROR_SEND_ERROR;
		req->req.length = 0;
		queue_complete_req(req);
	}
	return 0;
}