#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct skb_frag_struct {unsigned long page_offset; int size; int /*<<< orphan*/  page; } ;
struct sk_buff {int len; int data_len; char* data; } ;
struct qdio_buffer {TYPE_1__* element; } ;
struct TYPE_4__ {int nr_frags; struct skb_frag_struct* frags; } ;
struct TYPE_3__ {char* addr; int length; void* eflags; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 void* SBAL_EFLAGS_FIRST_FRAG ; 
 void* SBAL_EFLAGS_LAST_FRAG ; 
 void* SBAL_EFLAGS_MIDDLE_FRAG ; 
 unsigned long page_to_pfn (int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static inline void __qeth_fill_buffer_frag(struct sk_buff *skb,
		struct qdio_buffer *buffer, int is_tso,
		int *next_element_to_fill)
{
	struct skb_frag_struct *frag;
	int fragno;
	unsigned long addr;
	int element, cnt, dlen;

	fragno = skb_shinfo(skb)->nr_frags;
	element = *next_element_to_fill;
	dlen = 0;

	if (is_tso)
		buffer->element[element].eflags =
			SBAL_EFLAGS_MIDDLE_FRAG;
	else
		buffer->element[element].eflags =
			SBAL_EFLAGS_FIRST_FRAG;
	dlen = skb->len - skb->data_len;
	if (dlen) {
		buffer->element[element].addr = skb->data;
		buffer->element[element].length = dlen;
		element++;
	}
	for (cnt = 0; cnt < fragno; cnt++) {
		frag = &skb_shinfo(skb)->frags[cnt];
		addr = (page_to_pfn(frag->page) << PAGE_SHIFT) +
			frag->page_offset;
		buffer->element[element].addr = (char *)addr;
		buffer->element[element].length = frag->size;
		if (cnt < (fragno - 1))
			buffer->element[element].eflags =
				SBAL_EFLAGS_MIDDLE_FRAG;
		else
			buffer->element[element].eflags =
				SBAL_EFLAGS_LAST_FRAG;
		element++;
	}
	*next_element_to_fill = element;
}