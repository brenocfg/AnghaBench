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
struct TYPE_2__ {int max_delay; int min_delay; int /*<<< orphan*/  hw_lock; } ;
struct drm_i915_private {TYPE_1__ rps; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 unsigned int GEN6_PCODE_FREQ_IA_RATIO_SHIFT ; 
 int /*<<< orphan*/  GEN6_PCODE_WRITE_MIN_FREQ_TABLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int cpufreq_quick_get_max (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sandybridge_pcode_write (struct drm_i915_private*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int tsc_khz ; 

__attribute__((used)) static void gen6_update_ring_freq(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int min_freq = 15;
	int gpu_freq;
	unsigned int ia_freq, max_ia_freq;
	int scaling_factor = 180;

	WARN_ON(!mutex_is_locked(&dev_priv->rps.hw_lock));

	max_ia_freq = cpufreq_quick_get_max(0);
	/*
	 * Default to measured freq if none found, PCU will ensure we don't go
	 * over
	 */
	if (!max_ia_freq)
		max_ia_freq = tsc_khz;

	/* Convert from kHz to MHz */
	max_ia_freq /= 1000;

	/*
	 * For each potential GPU frequency, load a ring frequency we'd like
	 * to use for memory access.  We do this by specifying the IA frequency
	 * the PCU should use as a reference to determine the ring frequency.
	 */
	for (gpu_freq = dev_priv->rps.max_delay; gpu_freq >= dev_priv->rps.min_delay;
	     gpu_freq--) {
		int diff = dev_priv->rps.max_delay - gpu_freq;

		/*
		 * For GPU frequencies less than 750MHz, just use the lowest
		 * ring freq.
		 */
		if (gpu_freq < min_freq)
			ia_freq = 800;
		else
			ia_freq = max_ia_freq - ((diff * scaling_factor) / 2);
		ia_freq = DIV_ROUND_CLOSEST(ia_freq, 100);
		ia_freq <<= GEN6_PCODE_FREQ_IA_RATIO_SHIFT;

		sandybridge_pcode_write(dev_priv,
					GEN6_PCODE_WRITE_MIN_FREQ_TABLE,
					ia_freq | gpu_freq);
	}
}