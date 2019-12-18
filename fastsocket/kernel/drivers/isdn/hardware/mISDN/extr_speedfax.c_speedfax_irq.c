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
typedef  int u8 ;
struct sfax_hw {int /*<<< orphan*/  lock; int /*<<< orphan*/  name; int /*<<< orphan*/  isac; int /*<<< orphan*/  isar; int /*<<< orphan*/  irqcnt; scalar_t__ cfg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ISAC_ISTA ; 
 int /*<<< orphan*/  ISAR_IRQBIT ; 
 int ISAR_IRQSTA ; 
 int ReadISAC_IND (struct sfax_hw*,int /*<<< orphan*/ ) ; 
 int ReadISAR_IND (struct sfax_hw*,int /*<<< orphan*/ ) ; 
 int SFAX_TIGER_IRQ_BIT ; 
 scalar_t__ TIGER_AUX_STATUS ; 
 int inb (scalar_t__) ; 
 int irqloops ; 
 int /*<<< orphan*/  mISDNisac_irq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mISDNisar_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
speedfax_irq(int intno, void *dev_id)
{
	struct sfax_hw	*sf = dev_id;
	u8 val;
	int cnt = irqloops;

	spin_lock(&sf->lock);
	val = inb(sf->cfg + TIGER_AUX_STATUS);
	if (val & SFAX_TIGER_IRQ_BIT) { /* for us or shared ? */
		spin_unlock(&sf->lock);
		return IRQ_NONE; /* shared */
	}
	sf->irqcnt++;
	val = ReadISAR_IND(sf, ISAR_IRQBIT);
Start_ISAR:
	if (val & ISAR_IRQSTA)
		mISDNisar_irq(&sf->isar);
	val = ReadISAC_IND(sf, ISAC_ISTA);
	if (val)
		mISDNisac_irq(&sf->isac, val);
	val = ReadISAR_IND(sf, ISAR_IRQBIT);
	if ((val & ISAR_IRQSTA) && cnt--)
		goto Start_ISAR;
	if (cnt < irqloops)
		pr_debug("%s: %d irqloops cpu%d\n", sf->name,
			irqloops - cnt, smp_processor_id());
	if (irqloops && !cnt)
		pr_notice("%s: %d IRQ LOOP cpu%d\n", sf->name,
			irqloops, smp_processor_id());
	spin_unlock(&sf->lock);
	return IRQ_HANDLED;
}