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
typedef  int u8 ;
typedef  int u32 ;
struct pmac_i2c_pf_inst {int quirks; int* scratch; int const* buffer; } ;

/* Variables and functions */
 int pmac_i2c_quirk_invmask ; 

__attribute__((used)) static void pmac_i2c_do_apply_rmw(struct pmac_i2c_pf_inst *inst,
				  u32 len, const u8 *mask, const u8 *val)
{
	int i;

	if (inst->quirks & pmac_i2c_quirk_invmask) {
		for (i = 0; i < len; i ++)
			inst->scratch[i] = (inst->buffer[i] & mask[i]) | val[i];
	} else {
		for (i = 0; i < len; i ++)
			inst->scratch[i] = (inst->buffer[i] & ~mask[i])
				| (val[i] & mask[i]);
	}
}