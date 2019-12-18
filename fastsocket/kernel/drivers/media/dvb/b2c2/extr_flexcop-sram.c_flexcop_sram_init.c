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
struct flexcop_device {int rev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FC_SRAM_1_32KB ; 
 int /*<<< orphan*/  FC_SRAM_1_48KB ; 
#define  FLEXCOP_II 130 
#define  FLEXCOP_IIB 129 
#define  FLEXCOP_III 128 
 int /*<<< orphan*/  flexcop_sram_set_chip (struct flexcop_device*,int /*<<< orphan*/ ) ; 

int flexcop_sram_init(struct flexcop_device *fc)
{
	switch (fc->rev) {
	case FLEXCOP_II:
	case FLEXCOP_IIB:
		flexcop_sram_set_chip(fc, FC_SRAM_1_32KB);
		break;
	case FLEXCOP_III:
		flexcop_sram_set_chip(fc, FC_SRAM_1_48KB);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}