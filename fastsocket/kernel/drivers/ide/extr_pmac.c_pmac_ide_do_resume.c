#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  irq; scalar_t__ kauai_fcr; int /*<<< orphan*/  aapl_bus_id; int /*<<< orphan*/  node; int /*<<< orphan*/  mediabay; } ;
typedef  TYPE_1__ pmac_ide_hwif_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* feature_call ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_WAKEUP_DELAY ; 
 int KAUAI_FCR_UATA_ENABLE ; 
 int KAUAI_FCR_UATA_RESET_N ; 
 int /*<<< orphan*/  PMAC_FTR_IDE_ENABLE ; 
 int /*<<< orphan*/  PMAC_FTR_IDE_RESET ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_3__ ppc_md ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sanitize_timings (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int pmac_ide_do_resume(pmac_ide_hwif_t *pmif)
{
	/* Hard reset & re-enable controller (do we really need to reset ? -BenH) */
	if (!pmif->mediabay) {
		ppc_md.feature_call(PMAC_FTR_IDE_RESET, pmif->node, pmif->aapl_bus_id, 1);
		ppc_md.feature_call(PMAC_FTR_IDE_ENABLE, pmif->node, pmif->aapl_bus_id, 1);
		msleep(10);
		ppc_md.feature_call(PMAC_FTR_IDE_RESET, pmif->node, pmif->aapl_bus_id, 0);

		/* Kauai has it different */
		if (pmif->kauai_fcr) {
			u32 fcr = readl(pmif->kauai_fcr);
			fcr |= KAUAI_FCR_UATA_RESET_N | KAUAI_FCR_UATA_ENABLE;
			writel(fcr, pmif->kauai_fcr);
		}

		msleep(jiffies_to_msecs(IDE_WAKEUP_DELAY));
	}

	/* Sanitize drive timings */
	sanitize_timings(pmif);

	enable_irq(pmif->irq);

	return 0;
}