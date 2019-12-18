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
struct ehci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ehci_port_power (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_to_hcd (struct ehci_hcd*) ; 
 int /*<<< orphan*/  mpc83xx_usb_setup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehci_fsl_reinit(struct ehci_hcd *ehci)
{
	mpc83xx_usb_setup(ehci_to_hcd(ehci));
	ehci_port_power(ehci, 0);

	return 0;
}