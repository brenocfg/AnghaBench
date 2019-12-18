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
struct sk_buff {int len; int tail; } ;
struct inbuf_t {int inputstate; struct bc_state* bcs; struct cardstate* cs; } ;
struct cardstate {scalar_t__ dle; int /*<<< orphan*/  dev; } ;
struct bc_state {int inputstate; scalar_t__ fcs; unsigned char emptycount; int ignore; struct sk_buff* skb; } ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_HDLC ; 
 unsigned char DLE_FLAG ; 
 scalar_t__ HW_HDR_LEN ; 
 int INS_DLE_char ; 
 int INS_DLE_command ; 
 int INS_byte_stuff ; 
 int INS_have_data ; 
 int INS_skip_frame ; 
 unsigned char PPP_ESCAPE ; 
 unsigned char PPP_FLAG ; 
 scalar_t__ PPP_GOODFCS ; 
 scalar_t__ PPP_INITFCS ; 
 unsigned char PPP_TRANS ; 
 int SBUFSIZE ; 
 unsigned char* __skb_put (struct sk_buff*,int) ; 
 scalar_t__ crc_ccitt_byte (scalar_t__,unsigned char) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gigaset_rcv_error (struct sk_buff*,struct cardstate*,struct bc_state*) ; 
 int /*<<< orphan*/  gigaset_rcv_skb (struct sk_buff*,struct cardstate*,struct bc_state*) ; 
 scalar_t__ likely (int) ; 
 int muststuff (unsigned char) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int hdlc_loop(unsigned char c, unsigned char *src, int numbytes,
			    struct inbuf_t *inbuf)
{
	struct cardstate *cs = inbuf->cs;
	struct bc_state *bcs = inbuf->bcs;
	int inputstate = bcs->inputstate;
	__u16 fcs = bcs->fcs;
	struct sk_buff *skb = bcs->skb;
	unsigned char error;
	struct sk_buff *compskb;
	int startbytes = numbytes;
	int l;

	if (unlikely(inputstate & INS_byte_stuff)) {
		inputstate &= ~INS_byte_stuff;
		goto byte_stuff;
	}
	for (;;) {
		if (unlikely(c == PPP_ESCAPE)) {
			if (unlikely(!numbytes)) {
				inputstate |= INS_byte_stuff;
				break;
			}
			c = *src++;
			--numbytes;
			if (unlikely(c == DLE_FLAG &&
				     (cs->dle ||
				      inbuf->inputstate & INS_DLE_command))) {
				inbuf->inputstate |= INS_DLE_char;
				inputstate |= INS_byte_stuff;
				break;
			}
byte_stuff:
			c ^= PPP_TRANS;
			if (unlikely(!muststuff(c)))
				gig_dbg(DEBUG_HDLC, "byte stuffed: 0x%02x", c);
		} else if (unlikely(c == PPP_FLAG)) {
			if (unlikely(inputstate & INS_skip_frame)) {
#ifdef CONFIG_GIGASET_DEBUG
				if (!(inputstate & INS_have_data)) { /* 7E 7E */
					++bcs->emptycount;
				} else
					gig_dbg(DEBUG_HDLC,
					    "7e----------------------------");
#endif

				/* end of frame */
				error = 1;
				gigaset_rcv_error(NULL, cs, bcs);
			} else if (!(inputstate & INS_have_data)) { /* 7E 7E */
#ifdef CONFIG_GIGASET_DEBUG
				++bcs->emptycount;
#endif
				break;
			} else {
				gig_dbg(DEBUG_HDLC,
					"7e----------------------------");

				/* end of frame */
				error = 0;

				if (unlikely(fcs != PPP_GOODFCS)) {
					dev_err(cs->dev,
				"Checksum failed, %u bytes corrupted!\n",
						skb->len);
					compskb = NULL;
					gigaset_rcv_error(compskb, cs, bcs);
					error = 1;
				} else {
					if (likely((l = skb->len) > 2)) {
						skb->tail -= 2;
						skb->len -= 2;
					} else {
						dev_kfree_skb(skb);
						skb = NULL;
						inputstate |= INS_skip_frame;
						if (l == 1) {
							dev_err(cs->dev,
						  "invalid packet size (1)!\n");
							error = 1;
							gigaset_rcv_error(NULL,
								cs, bcs);
						}
					}
					if (likely(!(error ||
						     (inputstate &
						      INS_skip_frame)))) {
						gigaset_rcv_skb(skb, cs, bcs);
					}
				}
			}

			if (unlikely(error))
				if (skb)
					dev_kfree_skb(skb);

			fcs = PPP_INITFCS;
			inputstate &= ~(INS_have_data | INS_skip_frame);
			if (unlikely(bcs->ignore)) {
				inputstate |= INS_skip_frame;
				skb = NULL;
			} else if (likely((skb = dev_alloc_skb(SBUFSIZE + HW_HDR_LEN)) != NULL)) {
				skb_reserve(skb, HW_HDR_LEN);
			} else {
				dev_warn(cs->dev,
					 "could not allocate new skb\n");
				inputstate |= INS_skip_frame;
			}

			break;
		} else if (unlikely(muststuff(c))) {
			/* Should not happen. Possible after ZDLE=1<CR><LF>. */
			gig_dbg(DEBUG_HDLC, "not byte stuffed: 0x%02x", c);
		}

		/* add character */

#ifdef CONFIG_GIGASET_DEBUG
		if (unlikely(!(inputstate & INS_have_data))) {
			gig_dbg(DEBUG_HDLC, "7e (%d x) ================",
				bcs->emptycount);
			bcs->emptycount = 0;
		}
#endif

		inputstate |= INS_have_data;

		if (likely(!(inputstate & INS_skip_frame))) {
			if (unlikely(skb->len == SBUFSIZE)) {
				dev_warn(cs->dev, "received packet too long\n");
				dev_kfree_skb_any(skb);
				skb = NULL;
				inputstate |= INS_skip_frame;
				break;
			}
			*__skb_put(skb, 1) = c;
			fcs = crc_ccitt_byte(fcs, c);
		}

		if (unlikely(!numbytes))
			break;
		c = *src++;
		--numbytes;
		if (unlikely(c == DLE_FLAG &&
			     (cs->dle ||
			      inbuf->inputstate & INS_DLE_command))) {
			inbuf->inputstate |= INS_DLE_char;
			break;
		}
	}
	bcs->inputstate = inputstate;
	bcs->fcs = fcs;
	bcs->skb = skb;
	return startbytes - numbytes;
}