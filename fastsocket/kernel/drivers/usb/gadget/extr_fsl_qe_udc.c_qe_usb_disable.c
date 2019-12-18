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
struct TYPE_4__ {TYPE_1__* usb_regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  usb_usmod; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_MODE_EN ; 
 int /*<<< orphan*/  clrbits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* udc_controller ; 

__attribute__((used)) static inline void qe_usb_disable(void)
{
	clrbits8(&udc_controller->usb_regs->usb_usmod, USB_MODE_EN);
}