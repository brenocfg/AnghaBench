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
struct sk_buff {int dummy; } ;
struct audit_buffer {struct sk_buff* skb; } ;

/* Variables and functions */
 int AUDIT_BUFSIZ ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int audit_expand (struct audit_buffer*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 int skb_tailroom (struct sk_buff*) ; 

void audit_log_n_hex(struct audit_buffer *ab, const unsigned char *buf,
		size_t len)
{
	int i, avail, new_len;
	unsigned char *ptr;
	struct sk_buff *skb;
	static const unsigned char *hex = "0123456789ABCDEF";

	if (!ab)
		return;

	BUG_ON(!ab->skb);
	skb = ab->skb;
	avail = skb_tailroom(skb);
	new_len = len<<1;
	if (new_len >= avail) {
		/* Round the buffer request up to the next multiple */
		new_len = AUDIT_BUFSIZ*(((new_len-avail)/AUDIT_BUFSIZ) + 1);
		avail = audit_expand(ab, new_len);
		if (!avail)
			return;
	}

	ptr = skb_tail_pointer(skb);
	for (i=0; i<len; i++) {
		*ptr++ = hex[(buf[i] & 0xF0)>>4]; /* Upper nibble */
		*ptr++ = hex[buf[i] & 0x0F];	  /* Lower nibble */
	}
	*ptr = 0;
	skb_put(skb, len << 1); /* new string is twice the old string */
}