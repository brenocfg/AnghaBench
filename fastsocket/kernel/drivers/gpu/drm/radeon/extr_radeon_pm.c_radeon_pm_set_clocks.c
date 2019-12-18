#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct radeon_ring {int /*<<< orphan*/  ready; } ;
struct TYPE_6__ {scalar_t__ requested_clock_mode_index; scalar_t__ current_clock_mode_index; scalar_t__ requested_power_state_index; scalar_t__ current_power_state_index; int active_crtcs; int req_vblank; int /*<<< orphan*/  mclk_lock; int /*<<< orphan*/  dynpm_planned_action; scalar_t__ active_crtc_count; } ;
struct TYPE_5__ {scalar_t__ installed; } ;
struct radeon_device {int num_crtc; TYPE_3__* ddev; TYPE_2__ pm; int /*<<< orphan*/  ring_lock; TYPE_1__ irq; struct radeon_ring* ring; } ;
struct TYPE_7__ {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DYNPM_ACTION_NONE ; 
 int RADEON_NUM_RINGS ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_vblank_get (TYPE_3__*,int) ; 
 int /*<<< orphan*/  drm_vblank_put (TYPE_3__*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bandwidth_update (struct radeon_device*) ; 
 int radeon_fence_wait_empty_locked (struct radeon_device*,int) ; 
 int /*<<< orphan*/  radeon_set_power_state (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_unmap_vram_bos (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_update_bandwidth_info (struct radeon_device*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void radeon_pm_set_clocks(struct radeon_device *rdev)
{
	int i, r;

	/* no need to take locks, etc. if nothing's going to change */
	if ((rdev->pm.requested_clock_mode_index == rdev->pm.current_clock_mode_index) &&
	    (rdev->pm.requested_power_state_index == rdev->pm.current_power_state_index))
		return;

	mutex_lock(&rdev->ddev->struct_mutex);
	down_write(&rdev->pm.mclk_lock);
	mutex_lock(&rdev->ring_lock);

	/* wait for the rings to drain */
	for (i = 0; i < RADEON_NUM_RINGS; i++) {
		struct radeon_ring *ring = &rdev->ring[i];
		if (!ring->ready) {
			continue;
		}
		r = radeon_fence_wait_empty_locked(rdev, i);
		if (r) {
			/* needs a GPU reset dont reset here */
			mutex_unlock(&rdev->ring_lock);
			up_write(&rdev->pm.mclk_lock);
			mutex_unlock(&rdev->ddev->struct_mutex);
			return;
		}
	}

	radeon_unmap_vram_bos(rdev);

	if (rdev->irq.installed) {
		for (i = 0; i < rdev->num_crtc; i++) {
			if (rdev->pm.active_crtcs & (1 << i)) {
				rdev->pm.req_vblank |= (1 << i);
				drm_vblank_get(rdev->ddev, i);
			}
		}
	}

	radeon_set_power_state(rdev);

	if (rdev->irq.installed) {
		for (i = 0; i < rdev->num_crtc; i++) {
			if (rdev->pm.req_vblank & (1 << i)) {
				rdev->pm.req_vblank &= ~(1 << i);
				drm_vblank_put(rdev->ddev, i);
			}
		}
	}

	/* update display watermarks based on new power state */
	radeon_update_bandwidth_info(rdev);
	if (rdev->pm.active_crtc_count)
		radeon_bandwidth_update(rdev);

	rdev->pm.dynpm_planned_action = DYNPM_ACTION_NONE;

	mutex_unlock(&rdev->ring_lock);
	up_write(&rdev->pm.mclk_lock);
	mutex_unlock(&rdev->ddev->struct_mutex);
}