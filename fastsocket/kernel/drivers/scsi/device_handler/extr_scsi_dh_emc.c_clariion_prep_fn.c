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
struct request {int /*<<< orphan*/  cmd_flags; } ;
struct clariion_dh_data {scalar_t__ lun_state; } ;

/* Variables and functions */
 int BLKPREP_KILL ; 
 int BLKPREP_OK ; 
 scalar_t__ CLARIION_LUN_OWNED ; 
 int /*<<< orphan*/  REQ_QUIET ; 
 struct clariion_dh_data* get_clariion_data (struct scsi_device*) ; 

__attribute__((used)) static int clariion_prep_fn(struct scsi_device *sdev, struct request *req)
{
	struct clariion_dh_data *h = get_clariion_data(sdev);
	int ret = BLKPREP_OK;

	if (h->lun_state != CLARIION_LUN_OWNED) {
		ret = BLKPREP_KILL;
		req->cmd_flags |= REQ_QUIET;
	}
	return ret;

}