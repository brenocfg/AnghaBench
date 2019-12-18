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
struct TYPE_2__ {int plog_enabled; } ;
struct bfad_s {TYPE_1__ plog_buf; } ;
struct bfa_bsg_portlogctl_s {scalar_t__ ctl; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 scalar_t__ BFA_TRUE ; 

int
bfad_iocmd_porglog_ctl(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_portlogctl_s *iocmd = (struct bfa_bsg_portlogctl_s *)cmd;

	if (iocmd->ctl == BFA_TRUE)
		bfad->plog_buf.plog_enabled = 1;
	else
		bfad->plog_buf.plog_enabled = 0;

	iocmd->status = BFA_STATUS_OK;
	return 0;
}