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
struct TYPE_2__ {int /*<<< orphan*/  ioc; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; TYPE_1__ bfa; } ;
struct bfa_fw_stats_s {int dummy; } ;
struct bfa_bsg_ioc_fwstats_s {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ BFA_STATUS_OK ; 
 scalar_t__ BFA_STATUS_VERSION_FAIL ; 
 scalar_t__ bfa_ioc_fw_stats_get (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,int) ; 
 scalar_t__ bfad_chk_iocmd_sz (unsigned int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_ioc_get_fwstats(struct bfad_s *bfad, void *cmd,
			unsigned int payload_len)
{
	struct bfa_bsg_ioc_fwstats_s *iocmd =
			(struct bfa_bsg_ioc_fwstats_s *)cmd;
	void	*iocmd_bufptr;
	unsigned long	flags;

	if (bfad_chk_iocmd_sz(payload_len,
			sizeof(struct bfa_bsg_ioc_fwstats_s),
			sizeof(struct bfa_fw_stats_s)) != BFA_STATUS_OK) {
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		goto out;
	}

	iocmd_bufptr = (char *)iocmd + sizeof(struct bfa_bsg_ioc_fwstats_s);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_ioc_fw_stats_get(&bfad->bfa.ioc, iocmd_bufptr);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	if (iocmd->status != BFA_STATUS_OK) {
		bfa_trc(bfad, iocmd->status);
		goto out;
	}
out:
	bfa_trc(bfad, 0x6666);
	return 0;
}