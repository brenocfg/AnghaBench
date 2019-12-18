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
typedef  int /*<<< orphan*/  u32 ;
struct ssb_extif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_EXTIF_GPIO_OUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extif_write32_masked (struct ssb_extif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 ssb_extif_gpio_out(struct ssb_extif *extif, u32 mask, u32 value)
{
	return extif_write32_masked(extif, SSB_EXTIF_GPIO_OUT(0),
				   mask, value);
}