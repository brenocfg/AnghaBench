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
struct usb_host_interface {int /*<<< orphan*/  extralen; int /*<<< orphan*/  extra; } ;
struct uac2_output_terminal_descriptor {int bTerminalID; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAC_OUTPUT_TERMINAL ; 
 struct uac2_output_terminal_descriptor* snd_usb_find_csint_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uac2_output_terminal_descriptor*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct uac2_output_terminal_descriptor *
	snd_usb_find_output_terminal_descriptor(struct usb_host_interface *ctrl_iface,
						int terminal_id)
{
	struct uac2_output_terminal_descriptor *term = NULL;

	while ((term = snd_usb_find_csint_desc(ctrl_iface->extra,
					       ctrl_iface->extralen,
					       term, UAC_OUTPUT_TERMINAL))) {
		if (term->bTerminalID == terminal_id)
			return term;
	}

	return NULL;
}