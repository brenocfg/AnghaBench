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
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct qeth_card {int dummy; } ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int,int /*<<< orphan*/ ) ; 
 int QETH_MAX_BUFFER_ELEMENTS (struct qeth_card*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

int qeth_get_elements_no(struct qeth_card *card, void *hdr,
		     struct sk_buff *skb, int elems)
{
	int elements_needed = 0;

	if (skb_shinfo(skb)->nr_frags > 0)
		elements_needed = (skb_shinfo(skb)->nr_frags + 1);
	if (elements_needed == 0)
		elements_needed = 1 + (((((unsigned long) skb->data) %
				PAGE_SIZE) + skb->len) >> PAGE_SHIFT);
	if ((elements_needed + elems) > QETH_MAX_BUFFER_ELEMENTS(card)) {
		QETH_DBF_MESSAGE(2, "Invalid size of IP packet "
			"(Number=%d / Length=%d). Discarded.\n",
			(elements_needed+elems), skb->len);
		return 0;
	}
	return elements_needed;
}