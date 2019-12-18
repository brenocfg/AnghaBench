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
typedef  int uint32_t ;
struct smsm_shared {int state; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ID_SHARED_STATE ; 
 int MSM_SMSM_DEBUG ; 
 int SMSM_RESET ; 
 int /*<<< orphan*/  handle_modem_crash () ; 
 int msm_smd_debug_mask ; 
 int /*<<< orphan*/  notify_other_smsm () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 struct smsm_shared* smem_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smem_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int smsm_change_state(uint32_t clear_mask, uint32_t set_mask)
{
	unsigned long flags;
	struct smsm_shared *smsm;

	spin_lock_irqsave(&smem_lock, flags);

	smsm = smem_alloc(ID_SHARED_STATE,
			  2 * sizeof(struct smsm_shared));

	if (smsm) {
		if (smsm[1].state & SMSM_RESET)
			handle_modem_crash();
		smsm[0].state = (smsm[0].state & ~clear_mask) | set_mask;
		if (msm_smd_debug_mask & MSM_SMSM_DEBUG)
			pr_info("smsm_change_state %x\n",
			       smsm[0].state);
		notify_other_smsm();
	}

	spin_unlock_irqrestore(&smem_lock, flags);

	if (smsm == NULL) {
		pr_err("smsm_change_state <SM NO STATE>\n");
		return -EIO;
	}
	return 0;
}