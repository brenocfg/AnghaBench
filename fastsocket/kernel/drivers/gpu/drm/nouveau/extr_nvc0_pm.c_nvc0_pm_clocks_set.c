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
struct TYPE_3__ {scalar_t__ coef; } ;
struct nvc0_pm_state {TYPE_2__* eng; TYPE_1__ mem; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvc0_pm_state*) ; 
 int /*<<< orphan*/  prog_clk (struct drm_device*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  prog_mem (struct drm_device*,struct nvc0_pm_state*) ; 

int
nvc0_pm_clocks_set(struct drm_device *dev, void *data)
{
	struct nvc0_pm_state *info = data;
	int i;

	if (info->mem.coef)
		prog_mem(dev, info);

	for (i = 0; i < 16; i++) {
		if (!info->eng[i].freq)
			continue;
		prog_clk(dev, i, &info->eng[i]);
	}

	kfree(info);
	return 0;
}