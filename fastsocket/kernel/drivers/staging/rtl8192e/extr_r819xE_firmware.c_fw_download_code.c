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
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {unsigned char* data; scalar_t__ cb; } ;
struct r8192_priv {TYPE_1__* ieee80211; TYPE_2__* pFirmware; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ cmdpacket_frag_thresold; } ;
typedef  TYPE_2__ rt_firmware ;
typedef  int /*<<< orphan*/  dev ;
struct TYPE_6__ {scalar_t__ txbuf_size; void* bLastIniPkt; int /*<<< orphan*/  bCmdOrInit; int /*<<< orphan*/  queue_index; } ;
typedef  TYPE_3__ cb_desc ;
struct TYPE_4__ {int /*<<< orphan*/  (* softmac_hard_start_xmit ) (struct sk_buff*,struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_PACKET_TYPE_INIT ; 
 scalar_t__ MAX_DEV_ADDR_SIZE ; 
 int /*<<< orphan*/  TXCMD_QUEUE ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  firmware_init_param (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,struct net_device**,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static bool fw_download_code(struct net_device *dev, u8 *code_virtual_address,
			     u32 buffer_len)
{
	struct r8192_priv   *priv = ieee80211_priv(dev);
	bool 		    rt_status = true;
	u16		    frag_threshold;
	u16		    frag_length, frag_offset = 0;
	int		    i;

	rt_firmware	    *pfirmware = priv->pFirmware;
	struct sk_buff	    *skb;
	unsigned char	    *seg_ptr;
	cb_desc		    *tcb_desc;
	u8                  bLastIniPkt;

	firmware_init_param(dev);

	/* Fragmentation might be required */
	frag_threshold = pfirmware->cmdpacket_frag_thresold;
	do {
		if ((buffer_len - frag_offset) > frag_threshold) {
			frag_length = frag_threshold ;
			bLastIniPkt = 0;
		} else {
			frag_length = buffer_len - frag_offset;
			bLastIniPkt = 1;
		}

		/*
		 * Allocate skb buffer to contain firmware info and tx
		 * descriptor info add 4 to avoid packet appending overflow.
		 */
		skb  = dev_alloc_skb(frag_length + 4);
		memcpy((unsigned char *)(skb->cb), &dev, sizeof(dev));
		tcb_desc = (cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
		tcb_desc->queue_index = TXCMD_QUEUE;
		tcb_desc->bCmdOrInit = DESC_PACKET_TYPE_INIT;
		tcb_desc->bLastIniPkt = bLastIniPkt;

		seg_ptr = skb->data;

		/*
		 * Transform from little endian to big endian and pending zero
		 */
		for (i = 0; i < frag_length; i += 4) {
			*seg_ptr++ = ((i+0) < frag_length) ? code_virtual_address[i+3] : 0;
			*seg_ptr++ = ((i+1) < frag_length) ? code_virtual_address[i+2] : 0;
			*seg_ptr++ = ((i+2) < frag_length) ? code_virtual_address[i+1] : 0;
			*seg_ptr++ = ((i+3) < frag_length) ? code_virtual_address[i+0] : 0;
		}
		tcb_desc->txbuf_size = (u16)i;
		skb_put(skb, i);
		priv->ieee80211->softmac_hard_start_xmit(skb, dev);

		code_virtual_address += frag_length;
		frag_offset += frag_length;

	} while (frag_offset < buffer_len);

	return rt_status;
}