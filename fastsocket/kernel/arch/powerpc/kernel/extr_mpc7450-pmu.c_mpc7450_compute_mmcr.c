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
typedef  size_t u8 ;
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int MMCR0_PMC1CE ; 
 int MMCR0_PMCnCE ; 
 int N_CLASSES ; 
 int N_COUNTER ; 
 int PM_PMC_MSK ; 
 int PM_PMC_SH ; 
 int PM_THRESH_MSK ; 
 int PM_THRESH_SH ; 
 int PM_THRMULT_MSKS ; 
 int* classmap ; 
 int ffs (int) ; 
 int mpc7450_classify_event (int) ; 
 int mpc7450_threshold_use (int) ; 
 int* pmcsel_mask ; 
 int* pmcsel_shift ; 

__attribute__((used)) static int mpc7450_compute_mmcr(u64 event[], int n_ev,
				unsigned int hwc[], unsigned long mmcr[])
{
	u8 event_index[N_CLASSES][N_COUNTER];
	int n_classevent[N_CLASSES];
	int i, j, class, tuse;
	u32 pmc_inuse = 0, pmc_avail;
	u32 mmcr0 = 0, mmcr1 = 0, mmcr2 = 0;
	u32 ev, pmc, thresh;

	if (n_ev > N_COUNTER)
		return -1;

	/* First pass: count usage in each class */
	for (i = 0; i < N_CLASSES; ++i)
		n_classevent[i] = 0;
	for (i = 0; i < n_ev; ++i) {
		class = mpc7450_classify_event(event[i]);
		if (class < 0)
			return -1;
		j = n_classevent[class]++;
		event_index[class][j] = i;
	}

	/* Second pass: allocate PMCs from most specific event to least */
	for (class = N_CLASSES - 1; class >= 0; --class) {
		for (i = 0; i < n_classevent[class]; ++i) {
			ev = event[event_index[class][i]];
			if (class == 4) {
				pmc = (ev >> PM_PMC_SH) & PM_PMC_MSK;
				if (pmc_inuse & (1 << (pmc - 1)))
					return -1;
			} else {
				/* Find a suitable PMC */
				pmc_avail = classmap[class] & ~pmc_inuse;
				if (!pmc_avail)
					return -1;
				pmc = ffs(pmc_avail);
			}
			pmc_inuse |= 1 << (pmc - 1);

			tuse = mpc7450_threshold_use(ev);
			if (tuse) {
				thresh = (ev >> PM_THRESH_SH) & PM_THRESH_MSK;
				mmcr0 |= thresh << 16;
				if (tuse == 2 && (ev & PM_THRMULT_MSKS))
					mmcr2 = 0x80000000;
			}
			ev &= pmcsel_mask[pmc - 1];
			ev <<= pmcsel_shift[pmc - 1];
			if (pmc <= 2)
				mmcr0 |= ev;
			else
				mmcr1 |= ev;
			hwc[event_index[class][i]] = pmc - 1;
		}
	}

	if (pmc_inuse & 1)
		mmcr0 |= MMCR0_PMC1CE;
	if (pmc_inuse & 0x3e)
		mmcr0 |= MMCR0_PMCnCE;

	/* Return MMCRx values */
	mmcr[0] = mmcr0;
	mmcr[1] = mmcr1;
	mmcr[2] = mmcr2;
	return 0;
}