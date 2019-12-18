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
struct TYPE_6__ {int /*<<< orphan*/  complete; } ;
struct TYPE_5__ {unsigned int riddatalen; TYPE_2__ head; void* riddata; int /*<<< orphan*/  const* rridresp; } ;
typedef  TYPE_1__ usbctlx_rrid_completor_t ;
typedef  TYPE_2__ usbctlx_completor_t ;
typedef  int /*<<< orphan*/  hfa384x_usb_rridresp_t ;

/* Variables and functions */
 int /*<<< orphan*/  usbctlx_rrid_completor_fn ; 

__attribute__((used)) static inline usbctlx_completor_t *init_rrid_completor(usbctlx_rrid_completor_t
						       *completor,
						       const
						       hfa384x_usb_rridresp_t *
						       rridresp, void *riddata,
						       unsigned int riddatalen)
{
	completor->head.complete = usbctlx_rrid_completor_fn;
	completor->rridresp = rridresp;
	completor->riddata = riddata;
	completor->riddatalen = riddatalen;
	return &(completor->head);
}