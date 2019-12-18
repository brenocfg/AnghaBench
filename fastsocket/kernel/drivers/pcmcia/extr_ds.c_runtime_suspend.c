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
struct device {int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMSG_SUSPEND ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int pcmcia_dev_suspend (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int runtime_suspend(struct device *dev)
{
	int rc;

	down(&dev->sem);
	rc = pcmcia_dev_suspend(dev, PMSG_SUSPEND);
	up(&dev->sem);
	return rc;
}