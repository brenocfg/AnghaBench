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
struct TYPE_2__ {int /*<<< orphan*/  client; } ;
struct pmac_tumbler {TYPE_1__ i2c; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  TAS_REG_LMIX ; 
 int /*<<< orphan*/  TAS_REG_RMIX ; 
 scalar_t__ snapper_set_mix_vol1 (struct pmac_tumbler*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snapper_set_mix_vol(struct pmac_tumbler *mix, int idx)
{
	if (! mix->i2c.client)
		return -ENODEV;
	if (snapper_set_mix_vol1(mix, idx, 0, TAS_REG_LMIX) < 0 ||
	    snapper_set_mix_vol1(mix, idx, 1, TAS_REG_RMIX) < 0)
		return -EINVAL;
	return 0;
}