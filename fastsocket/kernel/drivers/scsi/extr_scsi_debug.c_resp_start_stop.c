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
struct sdebug_dev_info {int stopped; } ;
struct scsi_cmnd {scalar_t__ cmnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  INVALID_FIELD_IN_CDB ; 
 int check_condition_result ; 
 int check_readiness (struct scsi_cmnd*,int,struct sdebug_dev_info*) ; 
 int /*<<< orphan*/  mk_sense_buffer (struct sdebug_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resp_start_stop(struct scsi_cmnd * scp,
			   struct sdebug_dev_info * devip)
{
	unsigned char *cmd = (unsigned char *)scp->cmnd;
	int power_cond, errsts, start;

	if ((errsts = check_readiness(scp, 1, devip)))
		return errsts;
	power_cond = (cmd[4] & 0xf0) >> 4;
	if (power_cond) {
		mk_sense_buffer(devip, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB,
			       	0);
		return check_condition_result;
	}
	start = cmd[4] & 1;
	if (start == devip->stopped)
		devip->stopped = !start;
	return 0;
}