#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msix_entry {int dummy; } ;
struct bnad {int cfg_flags; int msix_num; int /*<<< orphan*/  bna_lock; TYPE_1__* msix_table; int /*<<< orphan*/  pcidev; } ;
struct TYPE_4__ {int entry; } ;

/* Variables and functions */
 int BNAD_CF_MSIX ; 
 int BNAD_MAILBOX_MSIX_VECTORS ; 
 int BNAD_NUM_RXP ; 
 int BNAD_NUM_TXQ ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bnad_q_num_adjust (struct bnad*,int,int) ; 
 int /*<<< orphan*/  bnad_q_num_init (struct bnad*) ; 
 TYPE_1__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int pci_enable_msix (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  pci_intx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
bnad_enable_msix(struct bnad *bnad)
{
	int i, ret;
	unsigned long flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	if (!(bnad->cfg_flags & BNAD_CF_MSIX)) {
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		return;
	}
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	if (bnad->msix_table)
		return;

	bnad->msix_table =
		kcalloc(bnad->msix_num, sizeof(struct msix_entry), GFP_KERNEL);

	if (!bnad->msix_table)
		goto intx_mode;

	for (i = 0; i < bnad->msix_num; i++)
		bnad->msix_table[i].entry = i;

	ret = pci_enable_msix(bnad->pcidev, bnad->msix_table, bnad->msix_num);
	if (ret > 0) {
		/* Not enough MSI-X vectors. */
		pr_warn("BNA: %d MSI-X vectors allocated < %d requested\n",
			ret, bnad->msix_num);

		spin_lock_irqsave(&bnad->bna_lock, flags);
		/* ret = #of vectors that we got */
		bnad_q_num_adjust(bnad, (ret - BNAD_MAILBOX_MSIX_VECTORS) / 2,
			(ret - BNAD_MAILBOX_MSIX_VECTORS) / 2);
		spin_unlock_irqrestore(&bnad->bna_lock, flags);

		bnad->msix_num = BNAD_NUM_TXQ + BNAD_NUM_RXP +
			 BNAD_MAILBOX_MSIX_VECTORS;

		if (bnad->msix_num > ret)
			goto intx_mode;

		/* Try once more with adjusted numbers */
		/* If this fails, fall back to INTx */
		ret = pci_enable_msix(bnad->pcidev, bnad->msix_table,
				      bnad->msix_num);
		if (ret)
			goto intx_mode;

	} else if (ret < 0)
		goto intx_mode;

	pci_intx(bnad->pcidev, 0);

	return;

intx_mode:
	pr_warn("BNA: MSI-X enable failed - operating in INTx mode\n");

	kfree(bnad->msix_table);
	bnad->msix_table = NULL;
	bnad->msix_num = 0;
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bnad->cfg_flags &= ~BNAD_CF_MSIX;
	bnad_q_num_init(bnad);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
}