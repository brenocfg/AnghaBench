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
struct hp_sw_dh_data {scalar_t__ path_state; } ;

/* Variables and functions */
 int BLKPREP_KILL ; 
 int BLKPREP_OK ; 
 scalar_t__ HP_SW_PATH_ACTIVE ; 
 int /*<<< orphan*/  REQ_QUIET ; 
 struct hp_sw_dh_data* get_hp_sw_data (struct scsi_device*) ; 

__attribute__((used)) static int hp_sw_prep_fn(struct scsi_device *sdev, struct request *req)
{
	struct hp_sw_dh_data *h = get_hp_sw_data(sdev);
	int ret = BLKPREP_OK;

	if (h->path_state != HP_SW_PATH_ACTIVE) {
		ret = BLKPREP_KILL;
		req->cmd_flags |= REQ_QUIET;
	}
	return ret;

}