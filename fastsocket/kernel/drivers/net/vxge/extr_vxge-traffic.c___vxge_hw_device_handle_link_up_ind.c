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
struct TYPE_2__ {int /*<<< orphan*/  (* link_up ) (struct __vxge_hw_device*) ;} ;
struct __vxge_hw_device {scalar_t__ link_state; TYPE_1__ uld_callbacks; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;

/* Variables and functions */
 scalar_t__ VXGE_HW_LINK_UP ; 
 int VXGE_HW_OK ; 
 int /*<<< orphan*/  stub1 (struct __vxge_hw_device*) ; 

enum vxge_hw_status
__vxge_hw_device_handle_link_up_ind(struct __vxge_hw_device *hldev)
{
	/*
	 * If the previous link state is not down, return.
	 */
	if (hldev->link_state == VXGE_HW_LINK_UP)
		goto exit;

	hldev->link_state = VXGE_HW_LINK_UP;

	/* notify driver */
	if (hldev->uld_callbacks.link_up)
		hldev->uld_callbacks.link_up(hldev);
exit:
	return VXGE_HW_OK;
}