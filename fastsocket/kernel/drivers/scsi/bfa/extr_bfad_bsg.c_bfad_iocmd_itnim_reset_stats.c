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
struct bfa_fcs_lport_s {int dummy; } ;
struct bfa_fcs_itnim_s {int dummy; } ;
struct bfa_bsg_rport_reset_stats_s {int /*<<< orphan*/  rpwwn; int /*<<< orphan*/  status; int /*<<< orphan*/  pwwn; int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFA_STATUS_UNKNOWN_LWWN ; 
 int /*<<< orphan*/  BFA_STATUS_UNKNOWN_RWWN ; 
 int /*<<< orphan*/  bfa_fcs_itnim_get_halitn (struct bfa_fcs_itnim_s*) ; 
 struct bfa_fcs_itnim_s* bfa_fcs_itnim_lookup (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_stats_clear (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ) ; 
 struct bfa_fcs_lport_s* bfa_fcs_lookup_port (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_itnim_clear_stats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
bfad_iocmd_itnim_reset_stats(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_rport_reset_stats_s *iocmd =
			(struct bfa_bsg_rport_reset_stats_s *)cmd;
	struct bfa_fcs_lport_s	*fcs_port;
	struct bfa_fcs_itnim_s	*itnim;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->pwwn);
	if (!fcs_port)
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
	else {
		itnim = bfa_fcs_itnim_lookup(fcs_port, iocmd->rpwwn);
		if (itnim == NULL)
			iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		else {
			iocmd->status = BFA_STATUS_OK;
			bfa_fcs_itnim_stats_clear(fcs_port, iocmd->rpwwn);
			bfa_itnim_clear_stats(bfa_fcs_itnim_get_halitn(itnim));
		}
	}
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	return 0;
}