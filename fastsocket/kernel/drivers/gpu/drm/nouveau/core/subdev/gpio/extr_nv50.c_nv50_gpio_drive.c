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
typedef  int u32 ;
struct nouveau_gpio {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ nv50_gpio_location (int,int*,int*) ; 
 int /*<<< orphan*/  nv_mask (struct nouveau_gpio*,int,int,int) ; 

__attribute__((used)) static int
nv50_gpio_drive(struct nouveau_gpio *gpio, int line, int dir, int out)
{
	u32 reg, shift;

	if (nv50_gpio_location(line, &reg, &shift))
		return -EINVAL;

	nv_mask(gpio, reg, 7 << shift, (((dir ^ 1) << 1) | out) << shift);
	return 0;
}