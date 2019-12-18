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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int pcmcia_socket_dev_resume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcc_drv_pcmcia_resume(struct platform_device *dev)
{
	return pcmcia_socket_dev_resume(&dev->dev);
}