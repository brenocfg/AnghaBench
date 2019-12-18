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
struct powerdomain {int dummy; } ;
struct TYPE_2__ {struct powerdomain* ptr; } ;
struct clockdomain {TYPE_1__ pwrdm; } ;

/* Variables and functions */

struct powerdomain *clkdm_get_pwrdm(struct clockdomain *clkdm)
{
	if (!clkdm)
		return NULL;

	return clkdm->pwrdm.ptr;
}