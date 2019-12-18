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

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PRINTR (char*,unsigned int) ; 
 struct sk_buff* alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int max (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlbufsiz ; 

__attribute__((used)) static struct sk_buff *ulog_alloc_skb(unsigned int size)
{
	struct sk_buff *skb;
	unsigned int n;

	/* alloc skb which should be big enough for a whole
	 * multipart message. WARNING: has to be <= 131000
	 * due to slab allocator restrictions */

	n = max(size, nlbufsiz);
	skb = alloc_skb(n, GFP_ATOMIC);
	if (!skb) {
		PRINTR("ipt_ULOG: can't alloc whole buffer %ub!\n", n);

		if (n > size) {
			/* try to allocate only as much as we need for
			 * current packet */

			skb = alloc_skb(size, GFP_ATOMIC);
			if (!skb)
				PRINTR("ipt_ULOG: can't even allocate %ub\n",
				       size);
		}
	}

	return skb;
}