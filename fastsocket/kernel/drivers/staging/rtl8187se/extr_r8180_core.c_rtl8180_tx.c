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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  txrdu; } ;
struct r8180_priv {int* txmapringtail; int* txmapring; int txringcount; int* txbkpringtail; int* txbkpring; int* txbepringtail; int* txbepring; int* txvipringtail; int* txvipring; int* txvopringtail; int* txvopring; int* txhpringtail; int* txhpring; int* txbeaconringtail; int* txbeaconring; int txbeaconcount; int rts; int txbuffsize; scalar_t__ card_8185; int plcp_preamble_mode; struct buffer* txhpbufstail; struct buffer* txvopbufstail; struct buffer* txvipbufstail; struct buffer* txbepbufstail; struct buffer* txbkpbufstail; struct buffer* txmapbufstail; int /*<<< orphan*/  hw_plcp_len; TYPE_3__* ieee80211; TYPE_1__ stats; int /*<<< orphan*/  NumTxUnicast; struct buffer* txbeaconbufstail; } ;
struct net_device {int dummy; } ;
struct ieee80211_hdr_3addr {int frame_ctl; int duration_id; int /*<<< orphan*/  addr1; } ;
struct buffer {int* buf; struct buffer* next; } ;
struct TYPE_5__ {int capability; } ;
struct TYPE_6__ {int basic_rate; TYPE_2__ current_network; } ;

/* Variables and functions */
#define  BEACON_PRIORITY 134 
#define  BE_PRIORITY 133 
#define  BK_PRIORITY 132 
 int ComputeTxTime (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMESGE (char*,int) ; 
 int /*<<< orphan*/  DMESGW (char*,int,int) ; 
 int ETH_ALEN ; 
#define  HI_PRIORITY 131 
 int IEEE80211_FCTL_MOREFRAGS ; 
#define  MANAGE_PRIORITY 130 
#define  VI_PRIORITY 129 
#define  VO_PRIORITY 128 
 int WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 int aSifsTime ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int ieeerate2rtlrate (int) ; 
 scalar_t__ is_broadcast_ether_addr (int*) ; 
 scalar_t__ is_multicast_ether_addr (int*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy (int**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8180_dma_kick (struct net_device*,int) ; 
 int rtl8180_len2duration (int,int,short*) ; 
 int rtl8180_rate2rate (int) ; 
 int sAckCtsLng ; 
 int sCrcLng ; 
 int /*<<< orphan*/  wmb () ; 

short rtl8180_tx(struct net_device *dev, u8* txbuf, int len, int priority,
		 short morefrag, short descfrag, int rate)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	u32 *tail,*temp_tail;
	u32 *begin;
	u32 *buf;
	int i;
	int remain;
	int buflen;
	int count;
	u16 duration;
	short ext;
	struct buffer* buflist;
	struct ieee80211_hdr_3addr *frag_hdr = (struct ieee80211_hdr_3addr *)txbuf;
	u8 dest[ETH_ALEN];
	u8			bUseShortPreamble = 0;
	u8			bCTSEnable = 0;
	u8			bRTSEnable = 0;
	u16 			Duration = 0;
	u16			RtsDur = 0;
	u16			ThisFrameTime = 0;
	u16			TxDescDuration = 0;
	u8 			ownbit_flag = false; //added by david woo for sync Tx, 2007.12.14

	switch(priority) {
	case MANAGE_PRIORITY:
		tail=priv->txmapringtail;
		begin=priv->txmapring;
		buflist = priv->txmapbufstail;
		count = priv->txringcount;
		break;
	case BK_PRIORITY:
		tail=priv->txbkpringtail;
		begin=priv->txbkpring;
		buflist = priv->txbkpbufstail;
		count = priv->txringcount;
		break;
	case BE_PRIORITY:
		tail=priv->txbepringtail;
		begin=priv->txbepring;
		buflist = priv->txbepbufstail;
		count = priv->txringcount;
		break;
	case VI_PRIORITY:
		tail=priv->txvipringtail;
		begin=priv->txvipring;
		buflist = priv->txvipbufstail;
		count = priv->txringcount;
		break;
	case VO_PRIORITY:
		tail=priv->txvopringtail;
		begin=priv->txvopring;
		buflist = priv->txvopbufstail;
		count = priv->txringcount;
		break;
	case HI_PRIORITY:
		tail=priv->txhpringtail;
		begin=priv->txhpring;
		buflist = priv->txhpbufstail;
		count = priv->txringcount;
		break;
	case BEACON_PRIORITY:
		tail=priv->txbeaconringtail;
		begin=priv->txbeaconring;
		buflist = priv->txbeaconbufstail;
		count = priv->txbeaconcount;
		break;
	default:
		return -1;
		break;
 	}

		memcpy(&dest, frag_hdr->addr1, ETH_ALEN);
		if (is_multicast_ether_addr(dest) ||
				is_broadcast_ether_addr(dest))
		{
			Duration = 0;
			RtsDur = 0;
			bRTSEnable = 0;
			bCTSEnable = 0;

			ThisFrameTime = ComputeTxTime(len + sCrcLng, rtl8180_rate2rate(rate), 0, bUseShortPreamble);
			TxDescDuration = ThisFrameTime;
		} else {// Unicast packet
			u16 AckTime;

			//YJ,add,080828,for Keep alive
			priv->NumTxUnicast++;

			// Figure out ACK rate according to BSS basic rate and Tx rate, 2006.03.08 by rcnjko.
			AckTime = ComputeTxTime(14, 10,0, 0);	// AckCTSLng = 14 use 1M bps send

			if ( ((len + sCrcLng) > priv->rts) && priv->rts )
			{ // RTS/CTS.
				u16 RtsTime, CtsTime;
				//u16 CtsRate;
				bRTSEnable = 1;
				bCTSEnable = 0;

				// Rate and time required for RTS.
				RtsTime = ComputeTxTime( sAckCtsLng/8,priv->ieee80211->basic_rate, 0, 0);
				// Rate and time required for CTS.
				CtsTime = ComputeTxTime(14, 10,0, 0);	// AckCTSLng = 14 use 1M bps send

				// Figure out time required to transmit this frame.
				ThisFrameTime = ComputeTxTime(len + sCrcLng,
						rtl8180_rate2rate(rate),
						0,
						bUseShortPreamble);

				// RTS-CTS-ThisFrame-ACK.
				RtsDur = CtsTime + ThisFrameTime + AckTime + 3*aSifsTime;

				TxDescDuration = RtsTime + RtsDur;
			}
			else {// Normal case.
				bCTSEnable = 0;
				bRTSEnable = 0;
				RtsDur = 0;

				ThisFrameTime = ComputeTxTime(len + sCrcLng, rtl8180_rate2rate(rate), 0, bUseShortPreamble);
				TxDescDuration = ThisFrameTime + aSifsTime + AckTime;
			}

			if(!(frag_hdr->frame_ctl & IEEE80211_FCTL_MOREFRAGS)) { //no more fragment
				// ThisFrame-ACK.
				Duration = aSifsTime + AckTime;
			} else { // One or more fragments remained.
				u16 NextFragTime;
				NextFragTime = ComputeTxTime( len + sCrcLng, //pretend following packet length equal current packet
						rtl8180_rate2rate(rate),
						0,
						bUseShortPreamble );

				//ThisFrag-ACk-NextFrag-ACK.
				Duration = NextFragTime + 3*aSifsTime + 2*AckTime;
			}

		} // End of Unicast packet

		frag_hdr->duration_id = Duration;

	buflen=priv->txbuffsize;
	remain=len;
	temp_tail = tail;

	while(remain!=0){
		mb();
		if(!buflist){
			DMESGE("TX buffer error, cannot TX frames. pri %d.", priority);
			return -1;
		}
		buf=buflist->buf;

		if ((*tail & (1 << 31)) && (priority != BEACON_PRIORITY)) {
			DMESGW("No more TX desc, returning %x of %x",
			       remain, len);
			priv->stats.txrdu++;
			return remain;
		}

		*tail= 0; // zeroes header
		*(tail+1) = 0;
		*(tail+3) = 0;
		*(tail+5) = 0;
		*(tail+6) = 0;
		*(tail+7) = 0;

		if(priv->card_8185){
			//FIXME: this should be triggered by HW encryption parameters.
			*tail |= (1<<15); //no encrypt
		}

		if(remain==len && !descfrag) {
			ownbit_flag = false;	//added by david woo,2007.12.14
			*tail = *tail| (1<<29) ; //fist segment of the packet
			*tail = *tail |(len);
		} else {
			ownbit_flag = true;
		}

		for(i=0;i<buflen&& remain >0;i++,remain--){
			((u8*)buf)[i]=txbuf[i]; //copy data into descriptor pointed DMAble buffer
			if(remain == 4 && i+4 >= buflen) break;
			/* ensure the last desc has at least 4 bytes payload */

		}
		txbuf = txbuf + i;
		*(tail+3)=*(tail+3) &~ 0xfff;
		*(tail+3)=*(tail+3) | i; // buffer lenght
		// Use short preamble or not
		if (priv->ieee80211->current_network.capability&WLAN_CAPABILITY_SHORT_PREAMBLE)
			if (priv->plcp_preamble_mode==1 && rate!=0)	//  short mode now, not long!
			;//	*tail |= (1<<16);				// enable short preamble mode.

		if(bCTSEnable) {
			*tail |= (1<<18);
		}

		if(bRTSEnable) //rts enable
		{
			*tail |= ((ieeerate2rtlrate(priv->ieee80211->basic_rate))<<19);//RTS RATE
			*tail |= (1<<23);//rts enable
			*(tail+1) |=(RtsDur&0xffff);//RTS Duration
		}
		*(tail+3) |= ((TxDescDuration&0xffff)<<16); //DURATION
//	        *(tail+3) |= (0xe6<<16);
        	*(tail+5) |= (11<<8);//(priv->retry_data<<8); //retry lim ;

		*tail = *tail | ((rate&0xf) << 24);

		/* hw_plcp_len is not used for rtl8180 chip */
		/* FIXME */
		if(priv->card_8185 == 0 || !priv->hw_plcp_len){
			duration = rtl8180_len2duration(len, rate, &ext);
			*(tail+1) = *(tail+1) | ((duration & 0x7fff)<<16);
			if(ext) *(tail+1) = *(tail+1) |(1<<31); //plcp length extension
		}

		if(morefrag) *tail = (*tail) | (1<<17); // more fragment
		if(!remain) *tail = (*tail) | (1<<28); // last segment of frame

               *(tail+5) = *(tail+5)|(2<<27);
                *(tail+7) = *(tail+7)|(1<<4);

		wmb();
		if(ownbit_flag)
		{
			*tail = *tail | (1<<31); // descriptor ready to be txed
		}

		if((tail - begin)/8 == count-1)
			tail=begin;
		else
			tail=tail+8;

		buflist=buflist->next;

		mb();

		switch(priority) {
			case MANAGE_PRIORITY:
				priv->txmapringtail=tail;
				priv->txmapbufstail=buflist;
				break;
			case BK_PRIORITY:
				priv->txbkpringtail=tail;
				priv->txbkpbufstail=buflist;
				break;
			case BE_PRIORITY:
				priv->txbepringtail=tail;
				priv->txbepbufstail=buflist;
				break;
			case VI_PRIORITY:
				priv->txvipringtail=tail;
				priv->txvipbufstail=buflist;
				break;
			case VO_PRIORITY:
				priv->txvopringtail=tail;
				priv->txvopbufstail=buflist;
				break;
			case HI_PRIORITY:
				priv->txhpringtail=tail;
				priv->txhpbufstail = buflist;
				break;
			case BEACON_PRIORITY:
				/* the HW seems to be happy with the 1st
				 * descriptor filled and the 2nd empty...
				 * So always update descriptor 1 and never
				 * touch 2nd
				 */
				break;
		}
	}
	*temp_tail = *temp_tail | (1<<31); // descriptor ready to be txed
	rtl8180_dma_kick(dev,priority);

	return 0;
}