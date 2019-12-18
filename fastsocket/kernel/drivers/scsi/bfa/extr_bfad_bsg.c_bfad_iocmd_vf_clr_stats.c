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
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa_fcs; } ;
struct bfa_vf_stats_s {int dummy; } ;
struct bfa_fcs_fabric_s {int /*<<< orphan*/  stats; } ;
struct bfa_bsg_vf_reset_stats_s {int /*<<< orphan*/  status; int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFA_STATUS_UNKNOWN_VFID ; 
 struct bfa_fcs_fabric_s* bfa_fcs_vf_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_vf_clr_stats(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_vf_reset_stats_s *iocmd =
			(struct bfa_bsg_vf_reset_stats_s *)cmd;
	struct bfa_fcs_fabric_s	*fcs_vf;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_vf = bfa_fcs_vf_lookup(&bfad->bfa_fcs, iocmd->vf_id);
	if (fcs_vf == NULL) {
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_VFID;
		goto out;
	}
	memset((void *)&fcs_vf->stats, 0, sizeof(struct bfa_vf_stats_s));
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	return 0;
}