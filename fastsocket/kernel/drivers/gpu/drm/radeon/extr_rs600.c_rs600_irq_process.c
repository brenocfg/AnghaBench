#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ hdmi0_status; scalar_t__ disp_int; } ;
struct TYPE_7__ {TYPE_2__ r500; } ;
struct TYPE_8__ {TYPE_3__ stat_regs; int /*<<< orphan*/ * pflip; int /*<<< orphan*/  vblank_queue; scalar_t__* crtc_vblank_int; } ;
struct TYPE_5__ {int vblank_sync; } ;
struct radeon_device {int family; scalar_t__ msi_enabled; int /*<<< orphan*/  audio_work; int /*<<< orphan*/  hotplug_work; TYPE_4__ irq; TYPE_1__ pm; int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
#define  CHIP_RS600 130 
#define  CHIP_RS690 129 
#define  CHIP_RS740 128 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 scalar_t__ G_000044_SW_INT (int) ; 
 scalar_t__ G_007404_HDMI0_AZ_FORMAT_WTRIG (scalar_t__) ; 
 scalar_t__ G_007EDC_DC_HOT_PLUG_DETECT1_INTERRUPT (scalar_t__) ; 
 scalar_t__ G_007EDC_DC_HOT_PLUG_DETECT2_INTERRUPT (scalar_t__) ; 
 scalar_t__ G_007EDC_LB_D1_VBLANK_INTERRUPT (scalar_t__) ; 
 scalar_t__ G_007EDC_LB_D2_VBLANK_INTERRUPT (scalar_t__) ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  RADEON_BUS_CNTL ; 
 int /*<<< orphan*/  RADEON_MSI_REARM_EN ; 
 int /*<<< orphan*/  RADEON_RING_TYPE_GFX_INDEX ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RS600_MSI_REARM ; 
 int RV370_MSI_REARM_EN ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_handle_vblank (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_crtc_handle_flip (struct radeon_device*,int) ; 
 int /*<<< orphan*/  radeon_fence_process (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int rs600_irq_ack (struct radeon_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int rs600_irq_process(struct radeon_device *rdev)
{
	u32 status, msi_rearm;
	bool queue_hotplug = false;
	bool queue_hdmi = false;

	status = rs600_irq_ack(rdev);
	if (!status &&
	    !rdev->irq.stat_regs.r500.disp_int &&
	    !rdev->irq.stat_regs.r500.hdmi0_status) {
		return IRQ_NONE;
	}
	while (status ||
	       rdev->irq.stat_regs.r500.disp_int ||
	       rdev->irq.stat_regs.r500.hdmi0_status) {
		/* SW interrupt */
		if (G_000044_SW_INT(status)) {
			radeon_fence_process(rdev, RADEON_RING_TYPE_GFX_INDEX);
		}
		/* Vertical blank interrupts */
		if (G_007EDC_LB_D1_VBLANK_INTERRUPT(rdev->irq.stat_regs.r500.disp_int)) {
			if (rdev->irq.crtc_vblank_int[0]) {
				drm_handle_vblank(rdev->ddev, 0);
				rdev->pm.vblank_sync = true;
				wake_up(&rdev->irq.vblank_queue);
			}
			if (atomic_read(&rdev->irq.pflip[0]))
				radeon_crtc_handle_flip(rdev, 0);
		}
		if (G_007EDC_LB_D2_VBLANK_INTERRUPT(rdev->irq.stat_regs.r500.disp_int)) {
			if (rdev->irq.crtc_vblank_int[1]) {
				drm_handle_vblank(rdev->ddev, 1);
				rdev->pm.vblank_sync = true;
				wake_up(&rdev->irq.vblank_queue);
			}
			if (atomic_read(&rdev->irq.pflip[1]))
				radeon_crtc_handle_flip(rdev, 1);
		}
		if (G_007EDC_DC_HOT_PLUG_DETECT1_INTERRUPT(rdev->irq.stat_regs.r500.disp_int)) {
			queue_hotplug = true;
			DRM_DEBUG("HPD1\n");
		}
		if (G_007EDC_DC_HOT_PLUG_DETECT2_INTERRUPT(rdev->irq.stat_regs.r500.disp_int)) {
			queue_hotplug = true;
			DRM_DEBUG("HPD2\n");
		}
		if (G_007404_HDMI0_AZ_FORMAT_WTRIG(rdev->irq.stat_regs.r500.hdmi0_status)) {
			queue_hdmi = true;
			DRM_DEBUG("HDMI0\n");
		}
		status = rs600_irq_ack(rdev);
	}
	if (queue_hotplug)
		schedule_work(&rdev->hotplug_work);
	if (queue_hdmi)
		schedule_work(&rdev->audio_work);
	if (rdev->msi_enabled) {
		switch (rdev->family) {
		case CHIP_RS600:
		case CHIP_RS690:
		case CHIP_RS740:
			msi_rearm = RREG32(RADEON_BUS_CNTL) & ~RS600_MSI_REARM;
			WREG32(RADEON_BUS_CNTL, msi_rearm);
			WREG32(RADEON_BUS_CNTL, msi_rearm | RS600_MSI_REARM);
			break;
		default:
			WREG32(RADEON_MSI_REARM_EN, RV370_MSI_REARM_EN);
			break;
		}
	}
	return IRQ_HANDLED;
}