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
struct i2c_child_t {int total_chnls; int /*<<< orphan*/ * mon_type; TYPE_1__* chnl_array; int /*<<< orphan*/  fan_mask; } ;
struct TYPE_2__ {size_t chnl_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVCTRL_FANSTAT_MON ; 
 int /*<<< orphan*/ * chnls_mask ; 

__attribute__((used)) static void envctrl_init_fanstat(struct i2c_child_t *pchild)
{
	int i;

	/* Go through all channels and set up the mask. */
	for (i = 0; i < pchild->total_chnls; i++)
		pchild->fan_mask |= chnls_mask[(pchild->chnl_array[i]).chnl_no];

	/* We only need to know if this child has fan status monitored.
	 * We don't care which channels since we have the mask already.
	 */
	pchild->mon_type[0] = ENVCTRL_FANSTAT_MON;
}