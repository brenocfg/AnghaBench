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
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa_fcs; } ;
struct bfa_itnim_iostats_s {int dummy; } ;
struct bfa_fcs_lport_s {int dummy; } ;
struct bfa_fcs_itnim_s {int dummy; } ;
struct bfa_bsg_itnim_iostats_s {int /*<<< orphan*/  iostats; int /*<<< orphan*/  status; int /*<<< orphan*/  rpwwn; int /*<<< orphan*/  lpwwn; int /*<<< orphan*/  vf_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFA_STATUS_UNKNOWN_LWWN ; 
 int /*<<< orphan*/  BFA_STATUS_UNKNOWN_RWWN ; 
 TYPE_1__* bfa_fcs_itnim_get_halitn (struct bfa_fcs_itnim_s*) ; 
 struct bfa_fcs_itnim_s* bfa_fcs_itnim_lookup (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ) ; 
 struct bfa_fcs_lport_s* bfa_fcs_lookup_port (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
bfad_iocmd_itnim_get_iostats(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_itnim_iostats_s *iocmd =
			(struct bfa_bsg_itnim_iostats_s *)cmd;
	struct bfa_fcs_lport_s *fcs_port;
	struct bfa_fcs_itnim_s *itnim;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->lpwwn);
	if (!fcs_port) {
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		bfa_trc(bfad, 0);
	} else {
		itnim = bfa_fcs_itnim_lookup(fcs_port, iocmd->rpwwn);
		if (itnim == NULL)
			iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		else {
			iocmd->status = BFA_STATUS_OK;
			if (bfa_fcs_itnim_get_halitn(itnim))
				memcpy((void *)&iocmd->iostats, (void *)
				&(bfa_fcs_itnim_get_halitn(itnim)->stats),
				       sizeof(struct bfa_itnim_iostats_s));
		}
	}
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	return 0;
}