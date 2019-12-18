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
struct sk_buff {scalar_t__ len; } ;
struct inbuf_t {int inputstate; struct bc_state* bcs; struct cardstate* cs; } ;
struct cardstate {int /*<<< orphan*/  dev; scalar_t__ dle; } ;
struct bc_state {int inputstate; int ignore; struct sk_buff* skb; } ;

/* Variables and functions */
 unsigned char DLE_FLAG ; 
 scalar_t__ HW_HDR_LEN ; 
 int INS_DLE_char ; 
 int INS_DLE_command ; 
 int INS_have_data ; 
 int INS_skip_frame ; 
 scalar_t__ SBUFSIZE ; 
 int /*<<< orphan*/ * __skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  bitrev8 (unsigned char) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gigaset_rcv_skb (struct sk_buff*,struct cardstate*,struct bc_state*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int iraw_loop(unsigned char c, unsigned char *src, int numbytes,
			    struct inbuf_t *inbuf)
{
	struct cardstate *cs = inbuf->cs;
	struct bc_state *bcs = inbuf->bcs;
	int inputstate = bcs->inputstate;
	struct sk_buff *skb = bcs->skb;
	int startbytes = numbytes;

	for (;;) {
		/* add character */
		inputstate |= INS_have_data;

		if (likely(!(inputstate & INS_skip_frame))) {
			if (unlikely(skb->len == SBUFSIZE)) {
				//FIXME just pass skb up and allocate a new one
				dev_warn(cs->dev, "received packet too long\n");
				dev_kfree_skb_any(skb);
				skb = NULL;
				inputstate |= INS_skip_frame;
				break;
			}
			*__skb_put(skb, 1) = bitrev8(c);
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

	/* pass data up */
	if (likely(inputstate & INS_have_data)) {
		if (likely(!(inputstate & INS_skip_frame))) {
			gigaset_rcv_skb(skb, cs, bcs);
		}
		inputstate &= ~(INS_have_data | INS_skip_frame);
		if (unlikely(bcs->ignore)) {
			inputstate |= INS_skip_frame;
			skb = NULL;
		} else if (likely((skb = dev_alloc_skb(SBUFSIZE + HW_HDR_LEN))
				  != NULL)) {
			skb_reserve(skb, HW_HDR_LEN);
		} else {
			dev_warn(cs->dev, "could not allocate new skb\n");
			inputstate |= INS_skip_frame;
		}
	}

	bcs->inputstate = inputstate;
	bcs->skb = skb;
	return startbytes - numbytes;
}