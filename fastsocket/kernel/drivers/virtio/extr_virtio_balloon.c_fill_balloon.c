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
struct virtio_balloon {size_t num_pfns; int /*<<< orphan*/  inflate_vq; int /*<<< orphan*/  pages; int /*<<< orphan*/  num_pages; int /*<<< orphan*/ * pfns; TYPE_1__* vdev; } ;
struct page {int /*<<< orphan*/  lru; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int GFP_HIGHUSER ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int __GFP_NOMEMALLOC ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t min (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  page_to_balloon_pfn (struct page*) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  tell_host (struct virtio_balloon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  totalram_pages ; 

__attribute__((used)) static void fill_balloon(struct virtio_balloon *vb, size_t num)
{
	/* We can only do one array worth at a time. */
	num = min(num, ARRAY_SIZE(vb->pfns));

	for (vb->num_pfns = 0; vb->num_pfns < num; vb->num_pfns++) {
		struct page *page = alloc_page(GFP_HIGHUSER | __GFP_NORETRY |
					__GFP_NOMEMALLOC | __GFP_NOWARN);
		if (!page) {
			if (printk_ratelimit())
				dev_printk(KERN_INFO, &vb->vdev->dev,
					   "Out of puff! Can't get %zu pages\n",
					   num);
			/* Sleep for at least 1/5 of a second before retry. */
			msleep(200);
			break;
		}
		vb->pfns[vb->num_pfns] = page_to_balloon_pfn(page);
		totalram_pages--;
		vb->num_pages++;
		list_add(&page->lru, &vb->pages);
	}

	/* Didn't get any?  Oh well. */
	if (vb->num_pfns == 0)
		return;

	tell_host(vb, vb->inflate_vq);
}