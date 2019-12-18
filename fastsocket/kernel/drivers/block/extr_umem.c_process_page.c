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
struct mm_page {size_t headcnt; size_t cnt; int idx; struct bio* bio; struct mm_dma_desc* desc; } ;
struct mm_dma_desc {int /*<<< orphan*/  transfer_size; int /*<<< orphan*/  local_addr; int /*<<< orphan*/  data_dma_handle; int /*<<< orphan*/  sem_control_bits; } ;
struct cardinfo {unsigned int dma_status; size_t Active; int init_size; int mm_size; int /*<<< orphan*/  lock; scalar_t__ check_batteries; TYPE_1__* dev; struct mm_page* mm_pages; } ;
struct bio {scalar_t__ bi_vcnt; scalar_t__ bi_idx; struct bio* bi_next; int /*<<< orphan*/  bi_rw; int /*<<< orphan*/  bi_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  bv_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_RW ; 
 int /*<<< orphan*/  BIO_UPTODATE ; 
 int DEBUG_LED_ON_TRANSFER ; 
 int DMASCR_DMA_COMPLETE ; 
 int DMASCR_HARD_ERROR ; 
 int DMASCR_TRANSFER_READ ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  LED_REMOVE ; 
 int /*<<< orphan*/  MEMORY_INITIALIZED ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  activate (struct cardinfo*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 TYPE_2__* bio_iovec_idx (struct bio*,int) ; 
 int /*<<< orphan*/  check_batteries (struct cardinfo*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int debug ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dump_dmastat (struct cardinfo*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_start_io (struct cardinfo*) ; 
 int /*<<< orphan*/  pci_unmap_page (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  reset_page (struct mm_page*) ; 
 int /*<<< orphan*/  set_led (struct cardinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_userbit (struct cardinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_page(unsigned long data)
{
	/* check if any of the requests in the page are DMA_COMPLETE,
	 * and deal with them appropriately.
	 * If we find a descriptor without DMA_COMPLETE in the semaphore, then
	 * dma must have hit an error on that descriptor, so use dma_status
	 * instead and assume that all following descriptors must be re-tried.
	 */
	struct mm_page *page;
	struct bio *return_bio = NULL;
	struct cardinfo *card = (struct cardinfo *)data;
	unsigned int dma_status = card->dma_status;

	spin_lock_bh(&card->lock);
	if (card->Active < 0)
		goto out_unlock;
	page = &card->mm_pages[card->Active];

	while (page->headcnt < page->cnt) {
		struct bio *bio = page->bio;
		struct mm_dma_desc *desc = &page->desc[page->headcnt];
		int control = le32_to_cpu(desc->sem_control_bits);
		int last = 0;
		int idx;

		if (!(control & DMASCR_DMA_COMPLETE)) {
			control = dma_status;
			last = 1;
		}
		page->headcnt++;
		idx = page->idx;
		page->idx++;
		if (page->idx >= bio->bi_vcnt) {
			page->bio = bio->bi_next;
			if (page->bio)
				page->idx = page->bio->bi_idx;
		}

		pci_unmap_page(card->dev, desc->data_dma_handle,
			       bio_iovec_idx(bio, idx)->bv_len,
				 (control & DMASCR_TRANSFER_READ) ?
				PCI_DMA_TODEVICE : PCI_DMA_FROMDEVICE);
		if (control & DMASCR_HARD_ERROR) {
			/* error */
			clear_bit(BIO_UPTODATE, &bio->bi_flags);
			dev_printk(KERN_WARNING, &card->dev->dev,
				"I/O error on sector %d/%d\n",
				le32_to_cpu(desc->local_addr)>>9,
				le32_to_cpu(desc->transfer_size));
			dump_dmastat(card, control);
		} else if (test_bit(BIO_RW, &bio->bi_rw) &&
			   le32_to_cpu(desc->local_addr) >> 9 ==
				card->init_size) {
			card->init_size += le32_to_cpu(desc->transfer_size) >> 9;
			if (card->init_size >> 1 >= card->mm_size) {
				dev_printk(KERN_INFO, &card->dev->dev,
					"memory now initialised\n");
				set_userbit(card, MEMORY_INITIALIZED, 1);
			}
		}
		if (bio != page->bio) {
			bio->bi_next = return_bio;
			return_bio = bio;
		}

		if (last)
			break;
	}

	if (debug & DEBUG_LED_ON_TRANSFER)
		set_led(card, LED_REMOVE, LED_OFF);

	if (card->check_batteries) {
		card->check_batteries = 0;
		check_batteries(card);
	}
	if (page->headcnt >= page->cnt) {
		reset_page(page);
		card->Active = -1;
		activate(card);
	} else {
		/* haven't finished with this one yet */
		pr_debug("do some more\n");
		mm_start_io(card);
	}
 out_unlock:
	spin_unlock_bh(&card->lock);

	while (return_bio) {
		struct bio *bio = return_bio;

		return_bio = bio->bi_next;
		bio->bi_next = NULL;
		bio_endio(bio, 0);
	}
}