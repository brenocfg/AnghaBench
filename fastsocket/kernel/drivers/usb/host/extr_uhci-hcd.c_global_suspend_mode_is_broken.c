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
struct uhci_hcd {int rh_numports; scalar_t__ io_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMI_BOARD_NAME ; 
 scalar_t__ USBPORTSC1 ; 
 int USBPORTSC_CCS ; 
 char* dmi_get_system_info (int /*<<< orphan*/ ) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int global_suspend_mode_is_broken(struct uhci_hcd *uhci)
{
	int port;
	const char *sys_info;
	static char bad_Asus_board[] = "A7V8X";

	/* One of Asus's motherboards has a bug which causes it to
	 * wake up immediately from suspend-to-RAM if any of the ports
	 * are connected.  In such cases we will not set EGSM.
	 */
	sys_info = dmi_get_system_info(DMI_BOARD_NAME);
	if (sys_info && !strcmp(sys_info, bad_Asus_board)) {
		for (port = 0; port < uhci->rh_numports; ++port) {
			if (inw(uhci->io_addr + USBPORTSC1 + port * 2) &
					USBPORTSC_CCS)
				return 1;
		}
	}

	return 0;
}