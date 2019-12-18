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
struct tsq_entry {int /*<<< orphan*/  word_2; } ;
struct TYPE_2__ {unsigned long paddr; struct tsq_entry* base; struct tsq_entry* next; struct tsq_entry* last; } ;
struct idt77252_dev {TYPE_1__ tsq; int /*<<< orphan*/  name; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSQSIZE ; 
 int /*<<< orphan*/  SAR_REG_TSQB ; 
 int /*<<< orphan*/  SAR_REG_TSQH ; 
 int /*<<< orphan*/  SAR_TSQE_INVALID ; 
 int /*<<< orphan*/  TSQSIZE ; 
 int TSQ_NUM_ENTRIES ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tsq_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tsq_entry* pci_alloc_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_tsq(struct idt77252_dev *card)
{
	struct tsq_entry *tsqe;

	card->tsq.base = pci_alloc_consistent(card->pcidev, RSQSIZE,
					      &card->tsq.paddr);
	if (card->tsq.base == NULL) {
		printk("%s: can't allocate TSQ.\n", card->name);
		return -1;
	}
	memset(card->tsq.base, 0, TSQSIZE);

	card->tsq.last = card->tsq.base + TSQ_NUM_ENTRIES - 1;
	card->tsq.next = card->tsq.last;
	for (tsqe = card->tsq.base; tsqe <= card->tsq.last; tsqe++)
		tsqe->word_2 = cpu_to_le32(SAR_TSQE_INVALID);

	writel(card->tsq.paddr, SAR_REG_TSQB);
	writel((unsigned long) card->tsq.next - (unsigned long) card->tsq.base,
	       SAR_REG_TSQH);

	return 0;
}