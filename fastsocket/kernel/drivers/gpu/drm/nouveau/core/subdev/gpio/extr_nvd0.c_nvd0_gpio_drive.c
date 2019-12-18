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
 int /*<<< orphan*/  nv_mask (struct nouveau_gpio*,int,int,int) ; 

int
nvd0_gpio_drive(struct nouveau_gpio *gpio, int line, int dir, int out)
{
	u32 data = ((dir ^ 1) << 13) | (out << 12);
	nv_mask(gpio, 0x00d610 + (line * 4), 0x00003000, data);
	nv_mask(gpio, 0x00d604, 0x00000001, 0x00000001); /* update? */
	return 0;
}