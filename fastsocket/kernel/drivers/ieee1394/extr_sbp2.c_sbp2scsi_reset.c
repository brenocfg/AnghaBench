#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
struct sbp2_lu {int dummy; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {scalar_t__* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBP2_INFO (char*) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  sbp2_agent_reset (struct sbp2_lu*,int) ; 
 scalar_t__ sbp2util_node_is_available (struct sbp2_lu*) ; 

__attribute__((used)) static int sbp2scsi_reset(struct scsi_cmnd *SCpnt)
{
	struct sbp2_lu *lu = (struct sbp2_lu *)SCpnt->device->host->hostdata[0];

	SBP2_INFO("reset requested");

	if (sbp2util_node_is_available(lu)) {
		SBP2_INFO("generating sbp2 fetch agent reset");
		sbp2_agent_reset(lu, 1);
	}

	return SUCCESS;
}