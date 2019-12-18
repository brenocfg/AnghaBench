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
struct sk_buff {int ip_summed; int /*<<< orphan*/  csum; } ;
typedef  int /*<<< orphan*/  __sum16 ;

/* Variables and functions */
#define  CHECKSUM_COMPLETE 129 
#define  CHECKSUM_NONE 128 
 int /*<<< orphan*/  __skb_checksum_complete (struct sk_buff*) ; 
 int /*<<< orphan*/  csum_fold (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __sum16 check_checksum(struct sk_buff *skb)
{
	__sum16 csum = 0;

	switch (skb->ip_summed) {
	case CHECKSUM_COMPLETE:
		csum = csum_fold(skb->csum);

		if (!csum)
			break;
		/* Fall through. */

	case CHECKSUM_NONE:
		skb->csum = 0;
		csum = __skb_checksum_complete(skb);
		skb->ip_summed = CHECKSUM_COMPLETE;
		break;
	}

	return csum;
}