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
struct i2c_child_t {int total_chnls; int /*<<< orphan*/ * mon_type; int /*<<< orphan*/  voltage_mask; TYPE_1__* chnl_array; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVCTRL_GLOBALADDR_MON ; 
 scalar_t__ PCF8584_VOLTAGE_TYPE ; 
 int /*<<< orphan*/ * chnls_mask ; 

__attribute__((used)) static void envctrl_init_globaladdr(struct i2c_child_t *pchild)
{
	int i;

	/* Voltage/PowerSupply monitoring is piggybacked 
	 * with Global Address on CompactPCI.  See comments
	 * within envctrl_i2c_globaladdr for bit assignments.
	 *
	 * The mask is created here by assigning mask bits to each
	 * bit position that represents PCF8584_VOLTAGE_TYPE data.
	 * Channel numbers are not consecutive within the globaladdr
	 * node (why?), so we use the actual counter value as chnls_mask
	 * index instead of the chnl_array[x].chnl_no value.
	 *
	 * NOTE: This loop could be replaced with a constant representing
	 * a mask of bits 5&6 (ENVCTRL_GLOBALADDR_PSTAT_MASK).
	 */
	for (i = 0; i < pchild->total_chnls; i++) {
		if (PCF8584_VOLTAGE_TYPE == pchild->chnl_array[i].type) {
			pchild->voltage_mask |= chnls_mask[i];
		}
	}

	/* We only need to know if this child has global addressing 
	 * line monitored.  We don't care which channels since we know 
	 * the mask already (ENVCTRL_GLOBALADDR_ADDR_MASK).
	 */
	pchild->mon_type[0] = ENVCTRL_GLOBALADDR_MON;
}