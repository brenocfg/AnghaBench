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
typedef  unsigned long long u64 ;
struct TYPE_4__ {unsigned int first_sendbuf; unsigned int last_sendbuf; } ;
struct qib_pportdata {unsigned long long sdma_descq_phys; unsigned long long sdma_head_phys; TYPE_2__ sdma_state; struct qib_devdata* dd; } ;
struct qib_devdata {unsigned int piobcnt2k; unsigned int piobcnt4k; TYPE_1__* cspec; } ;
struct TYPE_3__ {unsigned int sdmabufcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  kr_senddmabase ; 
 int /*<<< orphan*/  kr_senddmabufmask0 ; 
 int /*<<< orphan*/  kr_senddmabufmask1 ; 
 int /*<<< orphan*/  kr_senddmabufmask2 ; 
 int /*<<< orphan*/  kr_senddmaheadaddr ; 
 int /*<<< orphan*/  qib_sdma_7220_setlengen (struct qib_pportdata*) ; 
 int /*<<< orphan*/  qib_sdma_update_7220_tail (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static int init_sdma_7220_regs(struct qib_pportdata *ppd)
{
	struct qib_devdata *dd = ppd->dd;
	unsigned i, n;
	u64 senddmabufmask[3] = { 0 };

	/* Set SendDmaBase */
	qib_write_kreg(dd, kr_senddmabase, ppd->sdma_descq_phys);
	qib_sdma_7220_setlengen(ppd);
	qib_sdma_update_7220_tail(ppd, 0); /* Set SendDmaTail */
	/* Set SendDmaHeadAddr */
	qib_write_kreg(dd, kr_senddmaheadaddr, ppd->sdma_head_phys);

	/*
	 * Reserve all the former "kernel" piobufs, using high number range
	 * so we get as many 4K buffers as possible
	 */
	n = dd->piobcnt2k + dd->piobcnt4k;
	i = n - dd->cspec->sdmabufcnt;

	for (; i < n; ++i) {
		unsigned word = i / 64;
		unsigned bit = i & 63;

		BUG_ON(word >= 3);
		senddmabufmask[word] |= 1ULL << bit;
	}
	qib_write_kreg(dd, kr_senddmabufmask0, senddmabufmask[0]);
	qib_write_kreg(dd, kr_senddmabufmask1, senddmabufmask[1]);
	qib_write_kreg(dd, kr_senddmabufmask2, senddmabufmask[2]);

	ppd->sdma_state.first_sendbuf = i;
	ppd->sdma_state.last_sendbuf = n;

	return 0;
}