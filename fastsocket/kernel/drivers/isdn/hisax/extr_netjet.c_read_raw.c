#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_9__ {int* rec; int r_state; int r_one; int r_val; int r_bitcnt; int* rcvbuf; int /*<<< orphan*/  r_tot; void* r_fcs; int /*<<< orphan*/  r_err; } ;
struct TYPE_10__ {TYPE_3__ tiger; } ;
struct BCState {scalar_t__ mode; TYPE_4__ hw; int /*<<< orphan*/  err_inv; TYPE_5__* cs; int /*<<< orphan*/  err_crc; scalar_t__ channel; } ;
struct TYPE_7__ {int /*<<< orphan*/  irqstat0; } ;
struct TYPE_8__ {TYPE_1__ njet; } ;
struct TYPE_11__ {int debug; TYPE_2__ hw; } ;

/* Variables and functions */
 int HDLC_FLAG_FOUND ; 
 int HDLC_FLAG_SEARCH ; 
 int HDLC_FRAME_FOUND ; 
 int HDLC_ZERO_SEARCH ; 
 int HSCX_BUFMAX ; 
 int L1_DEB_HSCX ; 
 scalar_t__ L1_MODE_HDLC ; 
 int NETJET_DMA_RXSIZE ; 
 void* PPP_FCS (void*,int) ; 
 void* PPP_GOODFCS ; 
 void* PPP_INITFCS ; 
 int /*<<< orphan*/  debugl1 (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  got_frame (struct BCState*,int) ; 
 int /*<<< orphan*/  printframe (TYPE_5__*,int*,int,char*) ; 

__attribute__((used)) static void read_raw(struct BCState *bcs, u_int *buf, int cnt){
	int i;
	register u_char j;
	register u_char val;
	u_int  *pend = bcs->hw.tiger.rec +NETJET_DMA_RXSIZE -1;
	register u_char state = bcs->hw.tiger.r_state;
	register u_char r_one = bcs->hw.tiger.r_one;
	register u_char r_val = bcs->hw.tiger.r_val;
	register u_int bitcnt = bcs->hw.tiger.r_bitcnt;
	u_int *p = buf;
	int bits;
	u_char mask;

        if (bcs->mode == L1_MODE_HDLC) { // it's 64k
		mask = 0xff;
		bits = 8;
	}
	else { // it's 56K
		mask = 0x7f;
		bits = 7;
	};
	for (i=0;i<cnt;i++) {
		val = bcs->channel ? ((*p>>8) & 0xff) : (*p & 0xff);
		p++;
		if (p > pend)
			p = bcs->hw.tiger.rec;
		if ((val & mask) == mask) {
			state = HDLC_ZERO_SEARCH;
			bcs->hw.tiger.r_tot++;
			bitcnt = 0;
			r_one = 0;
			continue;
		}
		for (j=0;j<bits;j++) {
			if (state == HDLC_ZERO_SEARCH) {
				if (val & 1) {
					r_one++;
				} else {
					r_one=0;
					state= HDLC_FLAG_SEARCH;
					if (bcs->cs->debug & L1_DEB_HSCX)
						debugl1(bcs->cs,"tiger read_raw: zBit(%d,%d,%d) %x",
							bcs->hw.tiger.r_tot,i,j,val);
				}
			} else if (state == HDLC_FLAG_SEARCH) { 
				if (val & 1) {
					r_one++;
					if (r_one>6) {
						state=HDLC_ZERO_SEARCH;
					}
				} else {
					if (r_one==6) {
						bitcnt=0;
						r_val=0;
						state=HDLC_FLAG_FOUND;
						if (bcs->cs->debug & L1_DEB_HSCX)
							debugl1(bcs->cs,"tiger read_raw: flag(%d,%d,%d) %x",
								bcs->hw.tiger.r_tot,i,j,val);
					}
					r_one=0;
				}
			} else if (state ==  HDLC_FLAG_FOUND) {
				if (val & 1) {
					r_one++;
					if (r_one>6) {
						state=HDLC_ZERO_SEARCH;
					} else {
						r_val >>= 1;
						r_val |= 0x80;
						bitcnt++;
					}
				} else {
					if (r_one==6) {
						bitcnt=0;
						r_val=0;
						r_one=0;
						val >>= 1;
						continue;
					} else if (r_one!=5) {
						r_val >>= 1;
						r_val &= 0x7f;
						bitcnt++;
					}
					r_one=0;	
				}
				if ((state != HDLC_ZERO_SEARCH) &&
					!(bitcnt & 7)) {
					state=HDLC_FRAME_FOUND;
					bcs->hw.tiger.r_fcs = PPP_INITFCS;
					bcs->hw.tiger.rcvbuf[0] = r_val;
					bcs->hw.tiger.r_fcs = PPP_FCS (bcs->hw.tiger.r_fcs, r_val);
					if (bcs->cs->debug & L1_DEB_HSCX)
						debugl1(bcs->cs,"tiger read_raw: byte1(%d,%d,%d) rval %x val %x i %x",
							bcs->hw.tiger.r_tot,i,j,r_val,val,
							bcs->cs->hw.njet.irqstat0);
				}
			} else if (state ==  HDLC_FRAME_FOUND) {
				if (val & 1) {
					r_one++;
					if (r_one>6) {
						state=HDLC_ZERO_SEARCH;
						bitcnt=0;
					} else {
						r_val >>= 1;
						r_val |= 0x80;
						bitcnt++;
					}
				} else {
					if (r_one==6) {
						r_val=0; 
						r_one=0;
						bitcnt++;
						if (bitcnt & 7) {
							debugl1(bcs->cs, "tiger: frame not byte aligned");
							state=HDLC_FLAG_SEARCH;
							bcs->hw.tiger.r_err++;
#ifdef ERROR_STATISTIC
							bcs->err_inv++;
#endif
						} else {
							if (bcs->cs->debug & L1_DEB_HSCX)
								debugl1(bcs->cs,"tiger frame end(%d,%d): fcs(%x) i %x",
									i,j,bcs->hw.tiger.r_fcs, bcs->cs->hw.njet.irqstat0);
							if (bcs->hw.tiger.r_fcs == PPP_GOODFCS) {
								got_frame(bcs, (bitcnt>>3)-3);
							} else {
								if (bcs->cs->debug) {
									debugl1(bcs->cs, "tiger FCS error");
									printframe(bcs->cs, bcs->hw.tiger.rcvbuf,
										(bitcnt>>3)-1, "rec");
									bcs->hw.tiger.r_err++;
								}
#ifdef ERROR_STATISTIC
							bcs->err_crc++;
#endif
							}
							state=HDLC_FLAG_FOUND;
						}
						bitcnt=0;
					} else if (r_one==5) {
						val >>= 1;
						r_one=0;
						continue;
					} else {
						r_val >>= 1;
						r_val &= 0x7f;
						bitcnt++;
					}
					r_one=0;	
				}
				if ((state == HDLC_FRAME_FOUND) &&
					!(bitcnt & 7)) {
					if ((bitcnt>>3)>=HSCX_BUFMAX) {
						debugl1(bcs->cs, "tiger: frame too big");
						r_val=0; 
						state=HDLC_FLAG_SEARCH;
						bcs->hw.tiger.r_err++;
#ifdef ERROR_STATISTIC
						bcs->err_inv++;
#endif
					} else {
						bcs->hw.tiger.rcvbuf[(bitcnt>>3)-1] = r_val;
						bcs->hw.tiger.r_fcs = 
							PPP_FCS (bcs->hw.tiger.r_fcs, r_val);
					}
				}
			}
			val >>= 1;
		}
		bcs->hw.tiger.r_tot++;
	}
	bcs->hw.tiger.r_state = state;
	bcs->hw.tiger.r_one = r_one;
	bcs->hw.tiger.r_val = r_val;
	bcs->hw.tiger.r_bitcnt = bitcnt;
}