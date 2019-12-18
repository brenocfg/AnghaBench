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
struct TYPE_4__ {int calculation_running; scalar_t__ nr_samples; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct b43_wldev {TYPE_2__ noisecalc; TYPE_1__ phy; } ;

/* Variables and functions */
 scalar_t__ B43_PHYTYPE_G ; 
 int /*<<< orphan*/  b43_generate_noise_sample (struct b43_wldev*) ; 

__attribute__((used)) static void b43_calculate_link_quality(struct b43_wldev *dev)
{
	/* Top half of Link Quality calculation. */

	if (dev->phy.type != B43_PHYTYPE_G)
		return;
	if (dev->noisecalc.calculation_running)
		return;
	dev->noisecalc.calculation_running = true;
	dev->noisecalc.nr_samples = 0;

	b43_generate_noise_sample(dev);
}