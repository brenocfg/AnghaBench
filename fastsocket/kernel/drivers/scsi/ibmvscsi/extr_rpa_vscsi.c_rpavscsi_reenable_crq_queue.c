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
struct vio_dev {int /*<<< orphan*/  unit_address; } ;
struct ibmvscsi_host_data {int /*<<< orphan*/  dev; } ;
struct crq_queue {int dummy; } ;

/* Variables and functions */
 int H_BUSY ; 
 int /*<<< orphan*/  H_ENABLE_CRQ ; 
 int H_IN_PROGRESS ; 
 scalar_t__ H_IS_LONG_BUSY (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vio_dev* to_vio_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpavscsi_reenable_crq_queue(struct crq_queue *queue,
				       struct ibmvscsi_host_data *hostdata)
{
	int rc = 0;
	struct vio_dev *vdev = to_vio_dev(hostdata->dev);

	/* Re-enable the CRQ */
	do {
		if (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_ENABLE_CRQ, vdev->unit_address);
	} while ((rc == H_IN_PROGRESS) || (rc == H_BUSY) || (H_IS_LONG_BUSY(rc)));

	if (rc)
		dev_err(hostdata->dev, "Error %d enabling adapter\n", rc);
	return rc;
}