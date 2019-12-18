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
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa; } ;
struct bfa_fcpim_s {int /*<<< orphan*/  del_itn_stats; } ;
struct bfa_fcpim_del_itn_stats_s {int dummy; } ;
struct bfa_bsg_fcpim_del_itn_stats_s {int /*<<< orphan*/  status; int /*<<< orphan*/  modstats; } ;

/* Variables and functions */
 struct bfa_fcpim_s* BFA_FCPIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_fcpim_get_del_itn_stats(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_fcpim_del_itn_stats_s *iocmd =
			(struct bfa_bsg_fcpim_del_itn_stats_s *)cmd;
	struct bfa_fcpim_s *fcpim = BFA_FCPIM(&bfad->bfa);
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	memcpy((void *)&iocmd->modstats, (void *)&fcpim->del_itn_stats,
		sizeof(struct bfa_fcpim_del_itn_stats_s));
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	iocmd->status = BFA_STATUS_OK;
	return 0;
}