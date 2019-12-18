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
typedef  int u32 ;
struct ctlr_info {TYPE_1__* pdev; } ;
struct ReportLUNdata {scalar_t__ LUNListLength; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HPSA_MAX_LUN ; 
 int HPSA_MAX_PHYS_LUN ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 scalar_t__ hpsa_scsi_do_report_log_luns (struct ctlr_info*,struct ReportLUNdata*,int) ; 
 scalar_t__ hpsa_scsi_do_report_phys_luns (struct ctlr_info*,struct ReportLUNdata*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_gather_lun_info(struct ctlr_info *h,
	int reportlunsize,
	struct ReportLUNdata *physdev, u32 *nphysicals,
	struct ReportLUNdata *logdev, u32 *nlogicals)
{
	if (hpsa_scsi_do_report_phys_luns(h, physdev, reportlunsize, 0)) {
		dev_err(&h->pdev->dev, "report physical LUNs failed.\n");
		return -1;
	}
	*nphysicals = be32_to_cpu(*((__be32 *)physdev->LUNListLength)) / 8;
	if (*nphysicals > HPSA_MAX_PHYS_LUN) {
		dev_warn(&h->pdev->dev, "maximum physical LUNs (%d) exceeded."
			"  %d LUNs ignored.\n", HPSA_MAX_PHYS_LUN,
			*nphysicals - HPSA_MAX_PHYS_LUN);
		*nphysicals = HPSA_MAX_PHYS_LUN;
	}
	if (hpsa_scsi_do_report_log_luns(h, logdev, reportlunsize)) {
		dev_err(&h->pdev->dev, "report logical LUNs failed.\n");
		return -1;
	}
	*nlogicals = be32_to_cpu(*((__be32 *) logdev->LUNListLength)) / 8;
	/* Reject Logicals in excess of our max capability. */
	if (*nlogicals > HPSA_MAX_LUN) {
		dev_warn(&h->pdev->dev,
			"maximum logical LUNs (%d) exceeded.  "
			"%d LUNs ignored.\n", HPSA_MAX_LUN,
			*nlogicals - HPSA_MAX_LUN);
			*nlogicals = HPSA_MAX_LUN;
	}
	if (*nlogicals + *nphysicals > HPSA_MAX_PHYS_LUN) {
		dev_warn(&h->pdev->dev,
			"maximum logical + physical LUNs (%d) exceeded. "
			"%d LUNs ignored.\n", HPSA_MAX_PHYS_LUN,
			*nphysicals + *nlogicals - HPSA_MAX_PHYS_LUN);
		*nlogicals = HPSA_MAX_PHYS_LUN - *nphysicals;
	}
	return 0;
}