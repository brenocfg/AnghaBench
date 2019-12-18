#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int devicename; TYPE_1__* channel; } ;
struct TYPE_5__ {int msg_len; scalar_t__ buff_offset; } ;
struct TYPE_4__ {int next_sendbuf; int num_sendbufs; int /*<<< orphan*/  free_sendbufs; scalar_t__ first_sendbuf; } ;
typedef  TYPE_2__ LLData ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int /*<<< orphan*/  CEPID ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ISDN_STAT_BSENT ; 
 int /*<<< orphan*/  IS_VALID_CARD (int) ; 
 int /*<<< orphan*/  ceReqClass1 ; 
 int /*<<< orphan*/  ceReqLnkWrite ; 
 int /*<<< orphan*/  ceReqTypeLnk ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int get_card_from_id (int) ; 
 int /*<<< orphan*/  indicate_status (int,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  memcpy_toshmem (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 TYPE_3__** sc_adapter ; 
 int sendmessage (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int*) ; 

int sndpkt(int devId, int channel, int ack, struct sk_buff *data)
{
	LLData	ReqLnkWrite;
	int status;
	int card;
	unsigned long len;

	card = get_card_from_id(devId);

	if(!IS_VALID_CARD(card)) {
		pr_debug("invalid param: %d is not a valid card id\n", card);
		return -ENODEV;
	}

	pr_debug("%s: sndpkt: frst = 0x%lx nxt = %d  f = %d n = %d\n",
		sc_adapter[card]->devicename,
		sc_adapter[card]->channel[channel].first_sendbuf,
		sc_adapter[card]->channel[channel].next_sendbuf,
		sc_adapter[card]->channel[channel].free_sendbufs,
		sc_adapter[card]->channel[channel].num_sendbufs);

	if(!sc_adapter[card]->channel[channel].free_sendbufs) {
		pr_debug("%s: out of TX buffers\n",
				sc_adapter[card]->devicename);
		return -EINVAL;
	}

	if(data->len > BUFFER_SIZE) {
		pr_debug("%s: data overflows buffer size (data > buffer)\n",
			sc_adapter[card]->devicename);
		return -EINVAL;
	}

	ReqLnkWrite.buff_offset = sc_adapter[card]->channel[channel].next_sendbuf *
		BUFFER_SIZE + sc_adapter[card]->channel[channel].first_sendbuf;
	ReqLnkWrite.msg_len = data->len; /* sk_buff size */
	pr_debug("%s: writing %d bytes to buffer offset 0x%lx\n",
			sc_adapter[card]->devicename,
			ReqLnkWrite.msg_len, ReqLnkWrite.buff_offset);
	memcpy_toshmem(card, (char *)ReqLnkWrite.buff_offset, data->data, ReqLnkWrite.msg_len);

	/*
	 * sendmessage
	 */
	pr_debug("%s: sndpkt size=%d, buf_offset=0x%lx buf_indx=%d\n",
		sc_adapter[card]->devicename,
		ReqLnkWrite.msg_len, ReqLnkWrite.buff_offset,
		sc_adapter[card]->channel[channel].next_sendbuf);

	status = sendmessage(card, CEPID, ceReqTypeLnk, ceReqClass1, ceReqLnkWrite,
				channel+1, sizeof(LLData), (unsigned int*)&ReqLnkWrite);
	len = data->len;
	if(status) {
		pr_debug("%s: failed to send packet, status = %d\n",
				sc_adapter[card]->devicename, status);
		return -1;
	}
	else {
		sc_adapter[card]->channel[channel].free_sendbufs--;
		sc_adapter[card]->channel[channel].next_sendbuf =
			++sc_adapter[card]->channel[channel].next_sendbuf ==
			sc_adapter[card]->channel[channel].num_sendbufs ? 0 :
			sc_adapter[card]->channel[channel].next_sendbuf;
			pr_debug("%s: packet sent successfully\n", sc_adapter[card]->devicename);
		dev_kfree_skb(data);
		indicate_status(card,ISDN_STAT_BSENT,channel, (char *)&len);
	}
	return len;
}