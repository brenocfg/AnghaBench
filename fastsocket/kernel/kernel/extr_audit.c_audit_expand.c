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
struct sk_buff {int truesize; } ;
struct audit_buffer {int /*<<< orphan*/  gfp_mask; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_log_lost (char*) ; 
 int pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static inline int audit_expand(struct audit_buffer *ab, int extra)
{
	struct sk_buff *skb = ab->skb;
	int oldtail = skb_tailroom(skb);
	int ret = pskb_expand_head(skb, 0, extra, ab->gfp_mask);
	int newtail = skb_tailroom(skb);

	if (ret < 0) {
		audit_log_lost("out of memory in audit_expand");
		return 0;
	}

	skb->truesize += newtail - oldtail;
	return newtail;
}