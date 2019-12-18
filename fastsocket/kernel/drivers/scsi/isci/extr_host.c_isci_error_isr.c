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
struct isci_host {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  sci_controller_error_handler (struct isci_host*) ; 
 scalar_t__ sci_controller_error_isr (struct isci_host*) ; 

irqreturn_t isci_error_isr(int vec, void *data)
{
	struct isci_host *ihost = data;

	if (sci_controller_error_isr(ihost))
		sci_controller_error_handler(ihost);

	return IRQ_HANDLED;
}