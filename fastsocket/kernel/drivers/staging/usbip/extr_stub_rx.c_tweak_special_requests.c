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
struct urb {int /*<<< orphan*/  pipe; int /*<<< orphan*/  setup_packet; } ;

/* Variables and functions */
 scalar_t__ PIPE_CONTROL ; 
 scalar_t__ is_clear_halt_cmd (struct urb*) ; 
 scalar_t__ is_reset_device_cmd (struct urb*) ; 
 scalar_t__ is_set_configuration_cmd (struct urb*) ; 
 scalar_t__ is_set_interface_cmd (struct urb*) ; 
 int /*<<< orphan*/  tweak_clear_halt_cmd (struct urb*) ; 
 int /*<<< orphan*/  tweak_reset_device_cmd (struct urb*) ; 
 int /*<<< orphan*/  tweak_set_configuration_cmd (struct urb*) ; 
 int /*<<< orphan*/  tweak_set_interface_cmd (struct urb*) ; 
 scalar_t__ usb_pipetype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_dbg_stub_rx (char*) ; 

__attribute__((used)) static void tweak_special_requests(struct urb *urb)
{
	if (!urb || !urb->setup_packet)
		return;

	if (usb_pipetype(urb->pipe) != PIPE_CONTROL)
		return;

	if (is_clear_halt_cmd(urb))
		/* tweak clear_halt */
		 tweak_clear_halt_cmd(urb);

	else if (is_set_interface_cmd(urb))
		/* tweak set_interface */
		tweak_set_interface_cmd(urb);

	else if (is_set_configuration_cmd(urb))
		/* tweak set_configuration */
		tweak_set_configuration_cmd(urb);

	else if (is_reset_device_cmd(urb))
		tweak_reset_device_cmd(urb);
	else
		usbip_dbg_stub_rx("no need to tweak\n");
}