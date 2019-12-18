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
typedef  size_t u32 ;
struct __vxge_hw_device {int vpaths_deployed; int /*<<< orphan*/ * virtual_paths; TYPE_1__* common_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  tim_int_mask1; int /*<<< orphan*/  tim_int_mask0; } ;

/* Variables and functions */
 int /*<<< orphan*/  VXGE_HW_DEFAULT_32 ; 
 int /*<<< orphan*/  VXGE_HW_INTR_MASK_ALL ; 
 size_t VXGE_HW_MAX_VIRTUAL_PATHS ; 
 int /*<<< orphan*/  VXGE_HW_VIRTUAL_PATH_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __vxge_hw_pio_mem_write32_upper (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vxge_hw_device_mask_all (struct __vxge_hw_device*) ; 
 int /*<<< orphan*/  vxge_hw_vpath_intr_disable (int /*<<< orphan*/ ) ; 
 int vxge_mBIT (size_t) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void vxge_hw_device_intr_disable(struct __vxge_hw_device *hldev)
{
	u32 i;

	vxge_hw_device_mask_all(hldev);

	/* mask all the tim interrupts */
	writeq(VXGE_HW_INTR_MASK_ALL, &hldev->common_reg->tim_int_mask0);
	__vxge_hw_pio_mem_write32_upper(VXGE_HW_DEFAULT_32,
		&hldev->common_reg->tim_int_mask1);

	for (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) {

		if (!(hldev->vpaths_deployed & vxge_mBIT(i)))
			continue;

		vxge_hw_vpath_intr_disable(
			VXGE_HW_VIRTUAL_PATH_HANDLE(&hldev->virtual_paths[i]));
	}

	return;
}