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
struct jsm_channel {TYPE_1__* ch_bd; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 unsigned int ENXIO ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  IOCTL ; 
 int jsm_get_mstat (struct jsm_channel*) ; 
 int /*<<< orphan*/  jsm_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static unsigned int jsm_tty_get_mctrl(struct uart_port *port)
{
	int result;
	struct jsm_channel *channel = (struct jsm_channel *)port;

	jsm_printk(IOCTL, INFO, &channel->ch_bd->pci_dev, "start\n");

	result = jsm_get_mstat(channel);

	if (result < 0)
		return -ENXIO;

	jsm_printk(IOCTL, INFO, &channel->ch_bd->pci_dev, "finish\n");

	return result;
}