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
typedef  int u16 ;
struct usb_gadget {int dummy; } ;
struct TYPE_4__ {TYPE_1__* usb_param; } ;
struct TYPE_3__ {int /*<<< orphan*/  frame_n; } ;

/* Variables and functions */
 int EINVAL ; 
 int in_be16 (int /*<<< orphan*/ *) ; 
 TYPE_2__* udc_controller ; 

__attribute__((used)) static int qe_get_frame(struct usb_gadget *gadget)
{
	u16 tmp;

	tmp = in_be16(&udc_controller->usb_param->frame_n);
	if (tmp & 0x8000)
		tmp = tmp & 0x07ff;
	else
		tmp = -EINVAL;

	return (int)tmp;
}