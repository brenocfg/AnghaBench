#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct ehea_vsgentry {void* vaddr; int /*<<< orphan*/  len; void* l_key; } ;
struct TYPE_5__ {int /*<<< orphan*/  sg_list; struct ehea_vsgentry sg_entry; } ;
struct TYPE_6__ {TYPE_1__ immdata_desc; } ;
struct ehea_swqe {scalar_t__ descriptors; TYPE_2__ u; } ;
struct TYPE_7__ {scalar_t__ page_offset; int /*<<< orphan*/  page; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ skb_frag_t ;
struct TYPE_8__ {int nr_frags; TYPE_3__* frags; } ;

/* Variables and functions */
 void* ehea_map_vaddr (scalar_t__) ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  write_swqe2_immediate (struct sk_buff*,struct ehea_swqe*,void*) ; 

__attribute__((used)) static inline void write_swqe2_data(struct sk_buff *skb, struct net_device *dev,
				    struct ehea_swqe *swqe, u32 lkey)
{
	struct ehea_vsgentry *sg_list, *sg1entry, *sgentry;
	skb_frag_t *frag;
	int nfrags, sg1entry_contains_frag_data, i;

	nfrags = skb_shinfo(skb)->nr_frags;
	sg1entry = &swqe->u.immdata_desc.sg_entry;
	sg_list = (struct ehea_vsgentry *)&swqe->u.immdata_desc.sg_list;
	sg1entry_contains_frag_data = 0;

	write_swqe2_immediate(skb, swqe, lkey);

	/* write descriptors */
	if (nfrags > 0) {
		if (swqe->descriptors == 0) {
			/* sg1entry not yet used */
			frag = &skb_shinfo(skb)->frags[0];

			/* copy sg1entry data */
			sg1entry->l_key = lkey;
			sg1entry->len = frag->size;
			sg1entry->vaddr =
				ehea_map_vaddr(page_address(frag->page)
					       + frag->page_offset);
			swqe->descriptors++;
			sg1entry_contains_frag_data = 1;
		}

		for (i = sg1entry_contains_frag_data; i < nfrags; i++) {

			frag = &skb_shinfo(skb)->frags[i];
			sgentry = &sg_list[i - sg1entry_contains_frag_data];

			sgentry->l_key = lkey;
			sgentry->len = frag->size;
			sgentry->vaddr =
				ehea_map_vaddr(page_address(frag->page)
					       + frag->page_offset);
			swqe->descriptors++;
		}
	}
}