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
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct page* get_a_page (struct virtnet_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  give_pages (struct virtnet_info*,struct page*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int virtqueue_add_buf (int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ,int,struct page*) ; 

__attribute__((used)) static int add_recvbuf_mergeable(struct virtnet_info *vi, gfp_t gfp)
{
	struct page *page;
	struct scatterlist sg;
	int err;

	page = get_a_page(vi, gfp);
	if (!page)
		return -ENOMEM;

	sg_init_one(&sg, page_address(page), PAGE_SIZE);

	err = virtqueue_add_buf(vi->rvq, &sg, 0, 1, page);
	if (err < 0)
		give_pages(vi, page);

	return err;
}