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
struct uart_port {int dummy; } ;
struct serial_private {TYPE_1__* dev; } ;
struct pciserial_board {int /*<<< orphan*/  reg_shift; } ;
struct TYPE_2__ {int subsystem_device; } ;

/* Variables and functions */
 int pci_default_setup (struct serial_private*,struct pciserial_board const*,struct uart_port*,int) ; 
 int setup_port (struct serial_private*,struct uart_port*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_netmos_9900_setup(struct serial_private *priv,
				const struct pciserial_board *board,
				struct uart_port *port, int idx)
{
	unsigned int bar;

	if ((priv->dev->subsystem_device & 0xff00) == 0x3000) {
		/* netmos apparently orders BARs by datasheet layout, so serial
		 * ports get BARs 0 and 3 (or 1 and 4 for memmapped)
		 */
		bar = 3 * idx;

		return setup_port(priv, port, bar, 0, board->reg_shift);
	} else {
		return pci_default_setup(priv, board, port, idx);
	}
}