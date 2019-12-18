#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int off_pitch; } ;
struct TYPE_4__ {scalar_t__ pan_display; } ;
struct atyfb_par {int /*<<< orphan*/  irq; int /*<<< orphan*/  int_lock; TYPE_1__ crtc; TYPE_2__ vblank; int /*<<< orphan*/  irq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_INT_CNTL ; 
 int CRTC_INT_EN_MASK ; 
 int /*<<< orphan*/  CRTC_OFF_PITCH ; 
 int CRTC_VBLANK_INT_EN ; 
 int aty_ld_le32 (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aty_disable_irq(struct atyfb_par *par)
{
	u32 int_cntl;

	if (test_and_clear_bit(0, &par->irq_flags)) {
		if (par->vblank.pan_display) {
			par->vblank.pan_display = 0;
			aty_st_le32(CRTC_OFF_PITCH, par->crtc.off_pitch, par);
		}
		spin_lock_irq(&par->int_lock);
		int_cntl = aty_ld_le32(CRTC_INT_CNTL, par) & CRTC_INT_EN_MASK;
		/* disable interrupt */
		aty_st_le32(CRTC_INT_CNTL, int_cntl & ~CRTC_VBLANK_INT_EN, par);
		spin_unlock_irq(&par->int_lock);
		free_irq(par->irq, par);
	}

	return 0;
}