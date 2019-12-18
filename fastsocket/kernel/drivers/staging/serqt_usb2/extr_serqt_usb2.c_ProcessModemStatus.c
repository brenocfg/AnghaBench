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
struct quatech_port {unsigned char shadowMSR; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ProcessModemStatus(struct quatech_port *qt_port,
			       unsigned char modem_status)
{

	qt_port->shadowMSR = modem_status;
	wake_up_interruptible(&qt_port->wait);
	return;
}