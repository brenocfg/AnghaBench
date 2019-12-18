#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct iovec {scalar_t__ iov_base; scalar_t__ iov_len; } ;
struct dma_pinned_list {int nr_iovecs; struct dma_page_list* page_list; } ;
struct dma_page_list {int nr_pages; struct page** pages; scalar_t__ base_address; } ;
struct TYPE_5__ {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_4__ {TYPE_2__* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERNEL_DS ; 
 int /*<<< orphan*/  VERIFY_WRITE ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dma_unpin_iovec_pages (struct dma_pinned_list*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_fs () ; 
 int get_user_pages (TYPE_1__*,TYPE_2__*,unsigned long,int,int,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 struct dma_pinned_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 int num_pages_spanned (struct iovec*) ; 
 scalar_t__ segment_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct dma_pinned_list *dma_pin_iovec_pages(struct iovec *iov, size_t len)
{
	struct dma_pinned_list *local_list;
	struct page **pages;
	int i;
	int ret;
	int nr_iovecs = 0;
	int iovec_len_used = 0;
	int iovec_pages_used = 0;

	/* don't pin down non-user-based iovecs */
	if (segment_eq(get_fs(), KERNEL_DS))
		return NULL;

	/* determine how many iovecs/pages there are, up front */
	do {
		iovec_len_used += iov[nr_iovecs].iov_len;
		iovec_pages_used += num_pages_spanned(&iov[nr_iovecs]);
		nr_iovecs++;
	} while (iovec_len_used < len);

	/* single kmalloc for pinned list, page_list[], and the page arrays */
	local_list = kmalloc(sizeof(*local_list)
		+ (nr_iovecs * sizeof (struct dma_page_list))
		+ (iovec_pages_used * sizeof (struct page*)), GFP_KERNEL);
	if (!local_list)
		goto out;

	/* list of pages starts right after the page list array */
	pages = (struct page **) &local_list->page_list[nr_iovecs];

	local_list->nr_iovecs = 0;

	for (i = 0; i < nr_iovecs; i++) {
		struct dma_page_list *page_list = &local_list->page_list[i];

		len -= iov[i].iov_len;

		if (!access_ok(VERIFY_WRITE, iov[i].iov_base, iov[i].iov_len))
			goto unpin;

		page_list->nr_pages = num_pages_spanned(&iov[i]);
		page_list->base_address = iov[i].iov_base;

		page_list->pages = pages;
		pages += page_list->nr_pages;

		/* pin pages down */
		down_read(&current->mm->mmap_sem);
		ret = get_user_pages(
			current,
			current->mm,
			(unsigned long) iov[i].iov_base,
			page_list->nr_pages,
			1,	/* write */
			0,	/* force */
			page_list->pages,
			NULL);
		up_read(&current->mm->mmap_sem);

		if (ret != page_list->nr_pages)
			goto unpin;

		local_list->nr_iovecs = i + 1;
	}

	return local_list;

unpin:
	dma_unpin_iovec_pages(local_list);
out:
	return NULL;
}