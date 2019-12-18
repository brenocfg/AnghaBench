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
struct Scsi_Host {scalar_t__* hostdata; } ;
typedef  int /*<<< orphan*/  adpt_hba ;

/* Variables and functions */
 int /*<<< orphan*/  adpt_i2o_delete_hba (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_unregister (struct Scsi_Host*) ; 

__attribute__((used)) static int adpt_release(struct Scsi_Host *host)
{
	adpt_hba* pHba = (adpt_hba*) host->hostdata[0];
//	adpt_i2o_quiesce_hba(pHba);
	adpt_i2o_delete_hba(pHba);
	scsi_unregister(host);
	return 0;
}