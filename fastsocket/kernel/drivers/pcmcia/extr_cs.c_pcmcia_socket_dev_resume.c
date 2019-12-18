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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcmcia_socket_dev_run (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_resume ; 

int pcmcia_socket_dev_resume(struct device *dev)
{
	pcmcia_socket_dev_run(dev, socket_resume);
	return 0;
}