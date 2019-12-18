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
struct status_msg {scalar_t__ scsi_status; int /*<<< orphan*/  variable; } ;
struct st_ccb {int /*<<< orphan*/ * cmd; int /*<<< orphan*/  sense_bufflen; int /*<<< orphan*/ * sense_buffer; } ;

/* Variables and functions */
 scalar_t__ SAM_STAT_GOOD ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sg_copy_from_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void stex_copy_data(struct st_ccb *ccb,
	struct status_msg *resp, unsigned int variable)
{
	if (resp->scsi_status != SAM_STAT_GOOD) {
		if (ccb->sense_buffer != NULL)
			memcpy(ccb->sense_buffer, resp->variable,
				min(variable, ccb->sense_bufflen));
		return;
	}

	if (ccb->cmd == NULL)
		return;
	scsi_sg_copy_from_buffer(ccb->cmd, resp->variable, variable);
}