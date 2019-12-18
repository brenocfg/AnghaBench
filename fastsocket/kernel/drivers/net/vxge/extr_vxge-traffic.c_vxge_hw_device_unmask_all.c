#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ intr_mode; } ;
struct __vxge_hw_device {TYPE_2__* common_reg; TYPE_1__ config; } ;
struct TYPE_4__ {int /*<<< orphan*/  titan_mask_all_int; } ;

/* Variables and functions */
 scalar_t__ VXGE_HW_INTR_MODE_IRQLINE ; 
 int /*<<< orphan*/  VXGE_HW_TITAN_MASK_ALL_INT_TRAFFIC ; 
 int /*<<< orphan*/  __vxge_hw_pio_mem_write32_upper (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vxge_bVALn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void vxge_hw_device_unmask_all(struct __vxge_hw_device *hldev)
{
	u64 val64 = 0;

	if (hldev->config.intr_mode == VXGE_HW_INTR_MODE_IRQLINE)
		val64 =  VXGE_HW_TITAN_MASK_ALL_INT_TRAFFIC;

	__vxge_hw_pio_mem_write32_upper((u32)vxge_bVALn(val64, 0, 32),
			&hldev->common_reg->titan_mask_all_int);

	return;
}