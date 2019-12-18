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
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVFC_TMF_TGT_RESET ; 
 unsigned long ibmvfc_cancel_all (struct scsi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibmvfc_dev_cancel_all_reset(struct scsi_device *sdev, void *data)
{
	unsigned long *rc = data;
	*rc |= ibmvfc_cancel_all(sdev, IBMVFC_TMF_TGT_RESET);
}