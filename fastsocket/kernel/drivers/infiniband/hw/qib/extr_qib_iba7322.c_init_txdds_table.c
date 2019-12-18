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
struct txdds_ent {int dummy; } ;
struct qib_pportdata {int lflags; scalar_t__ link_speed_active; TYPE_1__* dd; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct txdds_ent const*) ; 
 int QIBL_LINKACTIVE ; 
 int QIBL_LINKARMED ; 
 int QIBL_LINKINIT ; 
 int QIB_HAS_QSFP ; 
 scalar_t__ QIB_IB_DDR ; 
 scalar_t__ QIB_IB_QDR ; 
 int TXDDS_TABLE_SZ ; 
 int /*<<< orphan*/  find_best_ent (struct qib_pportdata*,struct txdds_ent const**,struct txdds_ent const**,struct txdds_ent const**,int) ; 
 int /*<<< orphan*/  set_txdds (struct qib_pportdata*,int,struct txdds_ent const*) ; 
 struct txdds_ent const* txdds_ddr ; 
 struct txdds_ent const* txdds_qdr ; 
 struct txdds_ent const* txdds_sdr ; 
 int /*<<< orphan*/  write_tx_serdes_param (struct qib_pportdata*,struct txdds_ent*) ; 

__attribute__((used)) static void init_txdds_table(struct qib_pportdata *ppd, int override)
{
	const struct txdds_ent *sdr_dds, *ddr_dds, *qdr_dds;
	struct txdds_ent *dds;
	int idx;
	int single_ent = 0;

	find_best_ent(ppd, &sdr_dds, &ddr_dds, &qdr_dds, override);

	/* for mez cards or override, use the selected value for all entries */
	if (!(ppd->dd->flags & QIB_HAS_QSFP) || override)
		single_ent = 1;

	/* Fill in the first entry with the best entry found. */
	set_txdds(ppd, 0, sdr_dds);
	set_txdds(ppd, TXDDS_TABLE_SZ, ddr_dds);
	set_txdds(ppd, 2 * TXDDS_TABLE_SZ, qdr_dds);
	if (ppd->lflags & (QIBL_LINKINIT | QIBL_LINKARMED |
		QIBL_LINKACTIVE)) {
		dds = (struct txdds_ent *)(ppd->link_speed_active ==
					   QIB_IB_QDR ?  qdr_dds :
					   (ppd->link_speed_active ==
					    QIB_IB_DDR ? ddr_dds : sdr_dds));
		write_tx_serdes_param(ppd, dds);
	}

	/* Fill in the remaining entries with the default table values. */
	for (idx = 1; idx < ARRAY_SIZE(txdds_sdr); ++idx) {
		set_txdds(ppd, idx, single_ent ? sdr_dds : txdds_sdr + idx);
		set_txdds(ppd, idx + TXDDS_TABLE_SZ,
			  single_ent ? ddr_dds : txdds_ddr + idx);
		set_txdds(ppd, idx + 2 * TXDDS_TABLE_SZ,
			  single_ent ? qdr_dds : txdds_qdr + idx);
	}
}