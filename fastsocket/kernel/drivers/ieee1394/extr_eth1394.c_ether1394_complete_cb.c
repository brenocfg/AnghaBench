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
struct packet_task {scalar_t__ outstanding_pkts; int /*<<< orphan*/  hdr; int /*<<< orphan*/  max_payload; int /*<<< orphan*/  skb; struct hpsb_packet* packet; } ;
struct hpsb_packet {scalar_t__ tcode; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  ETH1394_PRINT_G (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ TCODE_STREAM_DATA ; 
 int /*<<< orphan*/  ether1394_dg_complete (struct packet_task*,int) ; 
 int ether1394_encapsulate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether1394_free_packet (struct hpsb_packet*) ; 
 int ether1394_send_packet (struct packet_task*,int) ; 
 int hpsb_packet_success (struct hpsb_packet*) ; 

__attribute__((used)) static void ether1394_complete_cb(void *__ptask)
{
	struct packet_task *ptask = (struct packet_task *)__ptask;
	struct hpsb_packet *packet = ptask->packet;
	int fail = 0;

	if (packet->tcode != TCODE_STREAM_DATA)
		fail = hpsb_packet_success(packet);

	ether1394_free_packet(packet);

	ptask->outstanding_pkts--;
	if (ptask->outstanding_pkts > 0 && !fail) {
		int tx_len, err;

		/* Add the encapsulation header to the fragment */
		tx_len = ether1394_encapsulate(ptask->skb, ptask->max_payload,
					       &ptask->hdr);
		err = ether1394_send_packet(ptask, tx_len);
		if (err) {
			if (err == -EAGAIN)
				ETH1394_PRINT_G(KERN_ERR, "Out of tlabels\n");

			ether1394_dg_complete(ptask, 1);
		}
	} else {
		ether1394_dg_complete(ptask, fail);
	}
}