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
struct macio_chip {scalar_t__ type; unsigned long flags; } ;
struct device_node {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ model_id; } ;

/* Variables and functions */
 long ENODEV ; 
 long EPERM ; 
 unsigned long HRW_RESET_SCC ; 
 unsigned long HRW_SCC_TRANS_EN_N ; 
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 unsigned long MACIO_FLAG_SCCA_ON ; 
 unsigned long MACIO_FLAG_SCCB_ON ; 
 int MACIO_FLAG_SCC_LOCKED ; 
 unsigned long MACIO_IN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_OUT32 (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  OHARE_FCR ; 
 unsigned long OH_SCCA_IO ; 
 unsigned long OH_SCCB_IO ; 
 unsigned long OH_SCC_ENABLE ; 
 unsigned long OH_SCC_RESET ; 
 long PMAC_SCC_FLAG_XMON ; 
 long PMAC_SCC_IRDA ; 
 scalar_t__ PMAC_TYPE_YIKES ; 
 scalar_t__ PMAC_TYPE_YOSEMITE ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 struct macio_chip* macio_find (struct device_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ macio_gatwick ; 
 scalar_t__ macio_heathrow ; 
 scalar_t__ macio_paddington ; 
 int /*<<< orphan*/  mdelay (int) ; 
 TYPE_1__ pmac_mb ; 
 int /*<<< orphan*/  pmu_enable_irled (int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static long ohare_htw_scc_enable(struct device_node *node, long param,
				 long value)
{
	struct macio_chip*	macio;
	unsigned long		chan_mask;
	unsigned long		fcr;
	unsigned long		flags;
	int			htw, trans;
	unsigned long		rmask;

	macio = macio_find(node, 0);
	if (!macio)
		return -ENODEV;
	if (!strcmp(node->name, "ch-a"))
		chan_mask = MACIO_FLAG_SCCA_ON;
	else if (!strcmp(node->name, "ch-b"))
		chan_mask = MACIO_FLAG_SCCB_ON;
	else
		return -ENODEV;

	htw = (macio->type == macio_heathrow || macio->type == macio_paddington
		|| macio->type == macio_gatwick);
	/* On these machines, the HRW_SCC_TRANS_EN_N bit mustn't be touched */
	trans = (pmac_mb.model_id != PMAC_TYPE_YOSEMITE &&
		 pmac_mb.model_id != PMAC_TYPE_YIKES);
	if (value) {
#ifdef CONFIG_ADB_PMU
		if ((param & 0xfff) == PMAC_SCC_IRDA)
			pmu_enable_irled(1);
#endif /* CONFIG_ADB_PMU */
		LOCK(flags);
		fcr = MACIO_IN32(OHARE_FCR);
		/* Check if scc cell need enabling */
		if (!(fcr & OH_SCC_ENABLE)) {
			fcr |= OH_SCC_ENABLE;
			if (htw) {
				/* Side effect: this will also power up the
				 * modem, but it's too messy to figure out on which
				 * ports this controls the tranceiver and on which
				 * it controls the modem
				 */
				if (trans)
					fcr &= ~HRW_SCC_TRANS_EN_N;
				MACIO_OUT32(OHARE_FCR, fcr);
				fcr |= (rmask = HRW_RESET_SCC);
				MACIO_OUT32(OHARE_FCR, fcr);
			} else {
				fcr |= (rmask = OH_SCC_RESET);
				MACIO_OUT32(OHARE_FCR, fcr);
			}
			UNLOCK(flags);
			(void)MACIO_IN32(OHARE_FCR);
			mdelay(15);
			LOCK(flags);
			fcr &= ~rmask;
			MACIO_OUT32(OHARE_FCR, fcr);
		}
		if (chan_mask & MACIO_FLAG_SCCA_ON)
			fcr |= OH_SCCA_IO;
		if (chan_mask & MACIO_FLAG_SCCB_ON)
			fcr |= OH_SCCB_IO;
		MACIO_OUT32(OHARE_FCR, fcr);
		macio->flags |= chan_mask;
		UNLOCK(flags);
		if (param & PMAC_SCC_FLAG_XMON)
			macio->flags |= MACIO_FLAG_SCC_LOCKED;
	} else {
		if (macio->flags & MACIO_FLAG_SCC_LOCKED)
			return -EPERM;
		LOCK(flags);
		fcr = MACIO_IN32(OHARE_FCR);
		if (chan_mask & MACIO_FLAG_SCCA_ON)
			fcr &= ~OH_SCCA_IO;
		if (chan_mask & MACIO_FLAG_SCCB_ON)
			fcr &= ~OH_SCCB_IO;
		MACIO_OUT32(OHARE_FCR, fcr);
		if ((fcr & (OH_SCCA_IO | OH_SCCB_IO)) == 0) {
			fcr &= ~OH_SCC_ENABLE;
			if (htw && trans)
				fcr |= HRW_SCC_TRANS_EN_N;
			MACIO_OUT32(OHARE_FCR, fcr);
		}
		macio->flags &= ~(chan_mask);
		UNLOCK(flags);
		mdelay(10);
#ifdef CONFIG_ADB_PMU
		if ((param & 0xfff) == PMAC_SCC_IRDA)
			pmu_enable_irled(0);
#endif /* CONFIG_ADB_PMU */
	}
	return 0;
}