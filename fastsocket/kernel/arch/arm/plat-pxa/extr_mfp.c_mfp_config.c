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
struct mfp_pin {unsigned long mfpr_run; unsigned long mfpr_lpm; unsigned long config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long MFPR_AF_SEL (int) ; 
 unsigned long MFPR_DRIVE (int) ; 
 int MFP_AF (unsigned long) ; 
 int MFP_DS (unsigned long) ; 
 int MFP_LPM_EDGE (unsigned long) ; 
 int MFP_LPM_STATE (unsigned long) ; 
 int MFP_PIN (unsigned long) ; 
 int MFP_PIN_MAX ; 
 int MFP_PULL (unsigned long) ; 
 int MFP_PULL_NONE ; 
 int /*<<< orphan*/  __mfp_config_run (struct mfp_pin*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mfp_spin_lock ; 
 struct mfp_pin* mfp_table ; 
 unsigned long* mfpr_edge ; 
 unsigned long* mfpr_lpm ; 
 unsigned long* mfpr_pull ; 
 int /*<<< orphan*/  mfpr_sync () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mfp_config(unsigned long *mfp_cfgs, int num)
{
	unsigned long flags;
	int i;

	spin_lock_irqsave(&mfp_spin_lock, flags);

	for (i = 0; i < num; i++, mfp_cfgs++) {
		unsigned long tmp, c = *mfp_cfgs;
		struct mfp_pin *p;
		int pin, af, drv, lpm, edge, pull;

		pin = MFP_PIN(c);
		BUG_ON(pin >= MFP_PIN_MAX);
		p = &mfp_table[pin];

		af  = MFP_AF(c);
		drv = MFP_DS(c);
		lpm = MFP_LPM_STATE(c);
		edge = MFP_LPM_EDGE(c);
		pull = MFP_PULL(c);

		/* run-mode pull settings will conflict with MFPR bits of
		 * low power mode state,  calculate mfpr_run and mfpr_lpm
		 * individually if pull != MFP_PULL_NONE
		 */
		tmp = MFPR_AF_SEL(af) | MFPR_DRIVE(drv);

		if (likely(pull == MFP_PULL_NONE)) {
			p->mfpr_run = tmp | mfpr_lpm[lpm] | mfpr_edge[edge];
			p->mfpr_lpm = p->mfpr_run;
		} else {
			p->mfpr_lpm = tmp | mfpr_lpm[lpm] | mfpr_edge[edge];
			p->mfpr_run = tmp | mfpr_pull[pull];
		}

		p->config = c; __mfp_config_run(p);
	}

	mfpr_sync();
	spin_unlock_irqrestore(&mfp_spin_lock, flags);
}