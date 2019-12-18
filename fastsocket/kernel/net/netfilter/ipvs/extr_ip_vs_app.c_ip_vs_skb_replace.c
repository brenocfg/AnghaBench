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
struct sk_buff {char* data; int len; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  tot_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EnterFunction (int) ; 
 int /*<<< orphan*/  LeaveFunction (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 scalar_t__ pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int,char*,int) ; 
 int /*<<< orphan*/  skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

int ip_vs_skb_replace(struct sk_buff *skb, gfp_t pri,
		      char *o_buf, int o_len, char *n_buf, int n_len)
{
	int diff;
	int o_offset;
	int o_left;

	EnterFunction(9);

	diff = n_len - o_len;
	o_offset = o_buf - (char *)skb->data;
	/* The length of left data after o_buf+o_len in the skb data */
	o_left = skb->len - (o_offset + o_len);

	if (diff <= 0) {
		memmove(o_buf + n_len, o_buf + o_len, o_left);
		memcpy(o_buf, n_buf, n_len);
		skb_trim(skb, skb->len + diff);
	} else if (diff <= skb_tailroom(skb)) {
		skb_put(skb, diff);
		memmove(o_buf + n_len, o_buf + o_len, o_left);
		memcpy(o_buf, n_buf, n_len);
	} else {
		if (pskb_expand_head(skb, skb_headroom(skb), diff, pri))
			return -ENOMEM;
		skb_put(skb, diff);
		memmove(skb->data + o_offset + n_len,
			skb->data + o_offset + o_len, o_left);
		skb_copy_to_linear_data_offset(skb, o_offset, n_buf, n_len);
	}

	/* must update the iph total length here */
	ip_hdr(skb)->tot_len = htons(skb->len);

	LeaveFunction(9);
	return 0;
}