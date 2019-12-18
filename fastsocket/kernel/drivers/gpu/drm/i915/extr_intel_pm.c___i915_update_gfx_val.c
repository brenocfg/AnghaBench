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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct TYPE_2__ {scalar_t__ last_count2; int gfx_power; struct timespec last_time2; } ;
struct drm_i915_private {TYPE_1__ ips; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFXEC ; 
 scalar_t__ I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int div_u64 (int,unsigned long) ; 
 int /*<<< orphan*/  getrawmonotonic (struct timespec*) ; 
 int /*<<< orphan*/  mchdev_lock ; 
 struct timespec timespec_sub (struct timespec,struct timespec) ; 

__attribute__((used)) static void __i915_update_gfx_val(struct drm_i915_private *dev_priv)
{
	struct timespec now, diff1;
	u64 diff;
	unsigned long diffms;
	u32 count;

	assert_spin_locked(&mchdev_lock);

	getrawmonotonic(&now);
	diff1 = timespec_sub(now, dev_priv->ips.last_time2);

	/* Don't divide by 0 */
	diffms = diff1.tv_sec * 1000 + diff1.tv_nsec / 1000000;
	if (!diffms)
		return;

	count = I915_READ(GFXEC);

	if (count < dev_priv->ips.last_count2) {
		diff = ~0UL - dev_priv->ips.last_count2;
		diff += count;
	} else {
		diff = count - dev_priv->ips.last_count2;
	}

	dev_priv->ips.last_count2 = count;
	dev_priv->ips.last_time2 = now;

	/* More magic constants... */
	diff = diff * 1181;
	diff = div_u64(diff, diffms * 10);
	dev_priv->ips.gfx_power = diff;
}