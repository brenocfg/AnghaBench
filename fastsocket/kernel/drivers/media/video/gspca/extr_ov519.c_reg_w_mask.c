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
typedef  int /*<<< orphan*/  u16 ;
struct sd {int dummy; } ;

/* Variables and functions */
 int reg_r (struct sd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reg_w_mask(struct sd *sd,
			u16 index,
			u8 value,
			u8 mask)
{
	int ret;
	u8 oldval;

	if (mask != 0xff) {
		value &= mask;			/* Enforce mask on value */
		ret = reg_r(sd, index);
		if (ret < 0)
			return;

		oldval = ret & ~mask;		/* Clear the masked bits */
		value |= oldval;		/* Set the desired bits */
	}
	reg_w(sd, index, value);
}