#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* attr; } ;
struct TYPE_9__ {TYPE_3__* plog; TYPE_2__ ioc; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; TYPE_4__ bfa; } ;
struct bfa_vhba_attr_s {int /*<<< orphan*/  path_tov; int /*<<< orphan*/  io_profile; scalar_t__ plog_enabled; int /*<<< orphan*/  nwwn; int /*<<< orphan*/  pwwn; } ;
struct bfa_bsg_vhba_attr_s {int /*<<< orphan*/  status; struct bfa_vhba_attr_s attr; } ;
typedef  scalar_t__ bfa_boolean_t ;
struct TYPE_8__ {scalar_t__ plog_enabled; } ;
struct TYPE_6__ {int /*<<< orphan*/  nwwn; int /*<<< orphan*/  pwwn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_fcpim_get_io_profile (TYPE_4__*) ; 
 int /*<<< orphan*/  bfa_fcpim_path_tov_get (TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_vhba_query(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_vhba_attr_s *iocmd =
			(struct bfa_bsg_vhba_attr_s *)cmd;
	struct bfa_vhba_attr_s *attr = &iocmd->attr;
	unsigned long flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	attr->pwwn =  bfad->bfa.ioc.attr->pwwn;
	attr->nwwn =  bfad->bfa.ioc.attr->nwwn;
	attr->plog_enabled = (bfa_boolean_t)bfad->bfa.plog->plog_enabled;
	attr->io_profile = bfa_fcpim_get_io_profile(&bfad->bfa);
	attr->path_tov  = bfa_fcpim_path_tov_get(&bfad->bfa);
	iocmd->status = BFA_STATUS_OK;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	return 0;
}