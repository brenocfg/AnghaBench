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
struct s2255_mode {int /*<<< orphan*/  bright; int /*<<< orphan*/  color; int /*<<< orphan*/  fdec; int /*<<< orphan*/  scale; int /*<<< orphan*/  format; } ;
struct s2255_dev {TYPE_1__* udev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 

__attribute__((used)) static void s2255_print_cfg(struct s2255_dev *sdev, struct s2255_mode *mode)
{
	struct device *dev = &sdev->udev->dev;
	dev_info(dev, "------------------------------------------------\n");
	dev_info(dev, "format: %d\nscale %d\n", mode->format, mode->scale);
	dev_info(dev, "fdec: %d\ncolor %d\n", mode->fdec, mode->color);
	dev_info(dev, "bright: 0x%x\n", mode->bright);
	dev_info(dev, "------------------------------------------------\n");
}