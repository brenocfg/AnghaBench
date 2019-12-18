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
struct ctlr_info {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hpsa_scsi_detect (struct ctlr_info*) ; 

__attribute__((used)) static int hpsa_register_scsi(struct ctlr_info *h)
{
	int rc;

	rc = hpsa_scsi_detect(h);
	if (rc != 0)
		dev_err(&h->pdev->dev, "hpsa_register_scsi: failed"
			" hpsa_scsi_detect(), rc is %d\n", rc);
	return rc;
}