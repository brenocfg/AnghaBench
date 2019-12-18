#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; scalar_t__ network_header; scalar_t__ tail; } ;
struct TYPE_3__ {int /*<<< orphan*/  tot_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_trim (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_send_check (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  skb_is_nonlinear (struct sk_buff*) ; 
 unsigned char* skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static void mangle_contents(struct sk_buff *skb,
			    unsigned int dataoff,
			    unsigned int match_offset,
			    unsigned int match_len,
			    const char *rep_buffer,
			    unsigned int rep_len)
{
	unsigned char *data;

	BUG_ON(skb_is_nonlinear(skb));
	data = skb_network_header(skb) + dataoff;

	/* move post-replacement */
	memmove(data + match_offset + rep_len,
		data + match_offset + match_len,
		skb->tail - (skb->network_header + dataoff +
			     match_offset + match_len));

	/* insert data from buffer */
	memcpy(data + match_offset, rep_buffer, rep_len);

	/* update skb info */
	if (rep_len > match_len) {
		pr_debug("nf_nat_mangle_packet: Extending packet by "
			 "%u from %u bytes\n", rep_len - match_len, skb->len);
		skb_put(skb, rep_len - match_len);
	} else {
		pr_debug("nf_nat_mangle_packet: Shrinking packet from "
			 "%u from %u bytes\n", match_len - rep_len, skb->len);
		__skb_trim(skb, skb->len + rep_len - match_len);
	}

	/* fix IP hdr checksum information */
	ip_hdr(skb)->tot_len = htons(skb->len);
	ip_send_check(ip_hdr(skb));
}