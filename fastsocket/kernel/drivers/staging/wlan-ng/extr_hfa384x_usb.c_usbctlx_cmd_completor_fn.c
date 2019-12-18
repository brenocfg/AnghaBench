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
typedef  int /*<<< orphan*/  usbctlx_completor_t ;
struct TYPE_2__ {int /*<<< orphan*/  result; int /*<<< orphan*/  cmdresp; } ;
typedef  TYPE_1__ usbctlx_cmd_completor_t ;

/* Variables and functions */
 int usbctlx_get_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbctlx_cmd_completor_fn(usbctlx_completor_t * head)
{
	usbctlx_cmd_completor_t *complete = (usbctlx_cmd_completor_t *) head;
	return usbctlx_get_status(complete->cmdresp, complete->result);
}