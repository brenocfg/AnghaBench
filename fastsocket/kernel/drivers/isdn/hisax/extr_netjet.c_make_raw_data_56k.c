#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
typedef  int u_char ;
struct TYPE_6__ {int* sendbuf; size_t sendcnt; int* sp; } ;
struct TYPE_7__ {TYPE_2__ tiger; } ;
struct BCState {TYPE_3__ hw; TYPE_1__* tx_skb; int /*<<< orphan*/  tx_cnt; TYPE_4__* cs; } ;
struct TYPE_8__ {int debug; } ;
struct TYPE_5__ {size_t len; int* data; } ;

/* Variables and functions */
 int HDLC_FLAG_VALUE ; 
 int L1_DEB_HSCX ; 
 int /*<<< orphan*/  MAKE_RAW_BYTE_56K ; 
 size_t PPP_FCS (size_t,int) ; 
 size_t PPP_INITFCS ; 
 int /*<<< orphan*/  debugl1 (TYPE_4__*,char*,...) ; 

__attribute__((used)) static int make_raw_data_56k(struct BCState *bcs) {
// this make_raw is for 56k
	register u_int i,s_cnt=0;
	register u_char j;
	register u_char val;
	register u_char s_one = 0;
	register u_char s_val = 0;
	register u_char bitcnt = 0;
	u_int fcs;
	
	if (!bcs->tx_skb) {
		debugl1(bcs->cs, "tiger make_raw_56k: NULL skb");
		return(1);
	}
	val = HDLC_FLAG_VALUE;
	for (j=0; j<8; j++) { 
		bitcnt++;
		s_val >>= 1;
		if (val & 1)
			s_val |= 0x80;
		else
			s_val &= 0x7f;
		if (bitcnt==7) {
			s_val >>= 1;
			s_val |= 0x80;
			bcs->hw.tiger.sendbuf[s_cnt++] = s_val;
			bitcnt = 0;
		}
		val >>= 1;
	};
	fcs = PPP_INITFCS;
	for (i=0; i<bcs->tx_skb->len; i++) {
		val = bcs->tx_skb->data[i];
		fcs = PPP_FCS (fcs, val);
		MAKE_RAW_BYTE_56K;
	}
	fcs ^= 0xffff;
	val = fcs & 0xff;
	MAKE_RAW_BYTE_56K;
	val = (fcs>>8) & 0xff;
	MAKE_RAW_BYTE_56K;
	val = HDLC_FLAG_VALUE;
	for (j=0; j<8; j++) { 
		bitcnt++;
		s_val >>= 1;
		if (val & 1)
			s_val |= 0x80;
		else
			s_val &= 0x7f;
		if (bitcnt==7) {
			s_val >>= 1;
			s_val |= 0x80;
			bcs->hw.tiger.sendbuf[s_cnt++] = s_val;
			bitcnt = 0;
		}
		val >>= 1;
	}
	if (bcs->cs->debug & L1_DEB_HSCX)
		debugl1(bcs->cs,"tiger make_raw_56k: in %ld out %d.%d",
			bcs->tx_skb->len, s_cnt, bitcnt);
	if (bitcnt) {
		while (8>bitcnt++) {
			s_val >>= 1;
			s_val |= 0x80;
		}
		bcs->hw.tiger.sendbuf[s_cnt++] = s_val;
		bcs->hw.tiger.sendbuf[s_cnt++] = 0xff;	// NJ<->NJ thoughput bug fix
	}
	bcs->hw.tiger.sendcnt = s_cnt;
	bcs->tx_cnt -= bcs->tx_skb->len;
	bcs->hw.tiger.sp = bcs->hw.tiger.sendbuf;
	return(0);
}