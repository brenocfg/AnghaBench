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
struct urb {unsigned char* transfer_buffer; int transfer_buffer_length; int number_of_packets; int /*<<< orphan*/  dev; TYPE_1__* iso_frame_desc; } ;
struct st5481_b_out {int flow_event; int /*<<< orphan*/  hdlc_state; struct sk_buff* tx_skb; struct urb** urb; int /*<<< orphan*/  busy; } ;
struct st5481_bcs {int channel; scalar_t__ mode; struct st5481_adapter* adapter; struct st5481_b_out b_out; } ;
struct st5481_adapter {int /*<<< orphan*/  usb_dev; } ;
struct sk_buff {int len; unsigned char* data; scalar_t__ truesize; } ;
struct TYPE_2__ {unsigned int offset; unsigned int length; } ;

/* Variables and functions */
 int B_FLOW_ADJUST ; 
 int /*<<< orphan*/  B_L1L2 (struct st5481_bcs*,int,void*) ; 
 int CONFIRM ; 
 int /*<<< orphan*/  DBG (int,char*,int,int) ; 
 int /*<<< orphan*/  DBG_ISO_PACKET (int,struct urb*) ; 
 int /*<<< orphan*/  DBG_SKB (int,struct sk_buff*) ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ L1_MODE_TRANS ; 
 int NUM_ISO_PACKETS_B ; 
 int OUT_DOWN ; 
 int OUT_UNDERRUN ; 
 int OUT_UP ; 
 int PH_DATA ; 
 int SIZE_ISO_PACKETS_B_OUT ; 
 int /*<<< orphan*/  SUBMIT_URB (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitrev8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ isdnhdlc_encode (int /*<<< orphan*/ *,unsigned char*,int,int*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_b_out(struct st5481_bcs *bcs,int buf_nr)
{
	struct st5481_b_out *b_out = &bcs->b_out;
	struct st5481_adapter *adapter = bcs->adapter;
	struct urb *urb;
	unsigned int packet_size,offset;
	int len,buf_size,bytes_sent;
	int i;
	struct sk_buff *skb;
	
	if (test_and_set_bit(buf_nr, &b_out->busy)) {
		DBG(4,"ep %d urb %d busy",(bcs->channel+1)*2,buf_nr);
		return;
	}
	urb = b_out->urb[buf_nr];

	// Adjust isoc buffer size according to flow state
	if(b_out->flow_event & (OUT_DOWN | OUT_UNDERRUN)) {
		buf_size = NUM_ISO_PACKETS_B*SIZE_ISO_PACKETS_B_OUT + B_FLOW_ADJUST;
		packet_size = SIZE_ISO_PACKETS_B_OUT + B_FLOW_ADJUST;
		DBG(4,"B%d,adjust flow,add %d bytes",bcs->channel+1,B_FLOW_ADJUST);
	} else if(b_out->flow_event & OUT_UP){
		buf_size = NUM_ISO_PACKETS_B*SIZE_ISO_PACKETS_B_OUT - B_FLOW_ADJUST;
		packet_size = SIZE_ISO_PACKETS_B_OUT - B_FLOW_ADJUST;
		DBG(4,"B%d,adjust flow,remove %d bytes",bcs->channel+1,B_FLOW_ADJUST);
	} else {
		buf_size = NUM_ISO_PACKETS_B*SIZE_ISO_PACKETS_B_OUT;
		packet_size = 8;
	}
	b_out->flow_event = 0;

	len = 0;
	while (len < buf_size) {
		if ((skb = b_out->tx_skb)) {
			DBG_SKB(0x100, skb);
			DBG(4,"B%d,len=%d",bcs->channel+1,skb->len);
			
			if (bcs->mode == L1_MODE_TRANS) {	
				bytes_sent = buf_size - len;
				if (skb->len < bytes_sent)
					bytes_sent = skb->len;
				{	/* swap tx bytes to get hearable audio data */
					register unsigned char *src  = skb->data;
					register unsigned char *dest = urb->transfer_buffer+len;
					register unsigned int count;
					for (count = 0; count < bytes_sent; count++)
						*dest++ = bitrev8(*src++);
				}
				len += bytes_sent;
			} else {
				len += isdnhdlc_encode(&b_out->hdlc_state,
						       skb->data, skb->len, &bytes_sent,
						       urb->transfer_buffer+len, buf_size-len);
			}

			skb_pull(skb, bytes_sent);

			if (!skb->len) {
				// Frame sent
				b_out->tx_skb = NULL;
				B_L1L2(bcs, PH_DATA | CONFIRM, (void *)(unsigned long) skb->truesize);
				dev_kfree_skb_any(skb);

/* 				if (!(bcs->tx_skb = skb_dequeue(&bcs->sq))) { */
/* 					st5481B_sched_event(bcs, B_XMTBUFREADY); */
/* 				} */
			}
		} else {
			if (bcs->mode == L1_MODE_TRANS) {
				memset(urb->transfer_buffer+len, 0xff, buf_size-len);
				len = buf_size;
			} else {
				// Send flags
				len += isdnhdlc_encode(&b_out->hdlc_state,
						       NULL, 0, &bytes_sent,
						       urb->transfer_buffer+len, buf_size-len);
			}
		}	
	}

	// Prepare the URB
	for (i = 0, offset = 0; offset < len; i++) {
		urb->iso_frame_desc[i].offset = offset;
		urb->iso_frame_desc[i].length = packet_size;
		offset += packet_size;
		packet_size = SIZE_ISO_PACKETS_B_OUT;
	}
	urb->transfer_buffer_length = len;
	urb->number_of_packets = i;
	urb->dev = adapter->usb_dev;

	DBG_ISO_PACKET(0x200,urb);

	SUBMIT_URB(urb, GFP_NOIO);
}