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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCP_TMF_LUN_RESET ; 
 int bnx2fc_initiate_tmf (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 

int bnx2fc_eh_device_reset(struct scsi_cmnd *sc_cmd)
{
	return bnx2fc_initiate_tmf(sc_cmd, FCP_TMF_LUN_RESET);
}