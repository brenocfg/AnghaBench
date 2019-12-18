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
struct page {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PSWPIN ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int PageUptodate (struct page*) ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_swap_bio_read ; 
 struct bio* get_swap_bio (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_bio (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int swap_readpage(struct page *page)
{
	struct bio *bio;
	int ret = 0;

	VM_BUG_ON(!PageLocked(page));
	VM_BUG_ON(PageUptodate(page));
	bio = get_swap_bio(GFP_KERNEL, page, end_swap_bio_read);
	if (bio == NULL) {
		unlock_page(page);
		ret = -ENOMEM;
		goto out;
	}
	count_vm_event(PSWPIN);
	submit_bio(READ, bio);
out:
	return ret;
}