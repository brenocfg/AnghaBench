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
struct serial_info {int ndev; int /*<<< orphan*/ * line; } ;
struct pcmcia_device {struct serial_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  serial8250_suspend_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int serial_suspend(struct pcmcia_device *link)
{
	struct serial_info *info = link->priv;
	int i;

	for (i = 0; i < info->ndev; i++)
		serial8250_suspend_port(info->line[i]);

	return 0;
}