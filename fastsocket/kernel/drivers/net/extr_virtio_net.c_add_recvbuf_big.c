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
struct virtnet_info {int /*<<< orphan*/  rvq; } ;
struct virtio_net_hdr {int dummy; } ;
struct scatterlist {int dummy; } ;
struct page {unsigned long private; } ;
struct padded_vnet_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int MAX_SKB_FRAGS ; 
 int PAGE_SIZE ; 
 struct page* get_a_page (struct virtnet_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  give_pages (struct virtnet_info*,struct page*) ; 
 char* page_address (struct page*) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,char*,int) ; 
 int virtqueue_add_buf (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int,struct page*) ; 

__attribute__((used)) static int add_recvbuf_big(struct virtnet_info *vi, gfp_t gfp)
{
	struct scatterlist sg[MAX_SKB_FRAGS + 2];
	struct page *first, *list = NULL;
	char *p;
	int i, err, offset;

	/* page in sg[MAX_SKB_FRAGS + 1] is list tail */
	for (i = MAX_SKB_FRAGS + 1; i > 1; --i) {
		first = get_a_page(vi, gfp);
		if (!first) {
			if (list)
				give_pages(vi, list);
			return -ENOMEM;
		}
		sg_set_buf(&sg[i], page_address(first), PAGE_SIZE);

		/* chain new page in list head to match sg */
		first->private = (unsigned long)list;
		list = first;
	}

	first = get_a_page(vi, gfp);
	if (!first) {
		give_pages(vi, list);
		return -ENOMEM;
	}
	p = page_address(first);

	/* sg[0], sg[1] share the same page */
	/* a separated sg[0] for  virtio_net_hdr only during to QEMU bug*/
	sg_set_buf(&sg[0], p, sizeof(struct virtio_net_hdr));

	/* sg[1] for data packet, from offset */
	offset = sizeof(struct padded_vnet_hdr);
	sg_set_buf(&sg[1], p + offset, PAGE_SIZE - offset);

	/* chain first in list head */
	first->private = (unsigned long)list;
	err = virtqueue_add_buf(vi->rvq, sg, 0, MAX_SKB_FRAGS + 2,
				       first);
	if (err < 0)
		give_pages(vi, first);

	return err;
}