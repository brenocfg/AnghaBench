#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  complete; } ;
typedef  TYPE_1__ usbctlx_completor_t ;
struct TYPE_6__ {TYPE_1__ head; int /*<<< orphan*/ * result; int /*<<< orphan*/  const* cmdresp; } ;
typedef  TYPE_2__ usbctlx_cmd_completor_t ;
typedef  int /*<<< orphan*/  hfa384x_usb_cmdresp_t ;
typedef  int /*<<< orphan*/  hfa384x_cmdresult_t ;

/* Variables and functions */
 int /*<<< orphan*/  usbctlx_cmd_completor_fn ; 

__attribute__((used)) static inline usbctlx_completor_t *init_cmd_completor(usbctlx_cmd_completor_t *
						      completor,
						      const
						      hfa384x_usb_cmdresp_t *
						      cmdresp,
						      hfa384x_cmdresult_t *
						      result)
{
	completor->head.complete = usbctlx_cmd_completor_fn;
	completor->cmdresp = cmdresp;
	completor->result = result;
	return &(completor->head);
}