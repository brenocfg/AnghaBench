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
typedef  void* u32 ;
struct ssp_device {scalar_t__ mmio_base; } ;
struct ssp_dev {int mode; int flags; int psp_flags; int speed; struct ssp_device* ssp; } ;

/* Variables and functions */
 scalar_t__ SSCR0 ; 
 scalar_t__ SSCR1 ; 
 scalar_t__ SSPSP ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 

int ssp_config(struct ssp_dev *dev, u32 mode, u32 flags, u32 psp_flags, u32 speed)
{
	struct ssp_device *ssp = dev->ssp;

	dev->mode = mode;
	dev->flags = flags;
	dev->psp_flags = psp_flags;
	dev->speed = speed;

	/* set up port type, speed, port settings */
	__raw_writel((dev->speed | dev->mode), ssp->mmio_base + SSCR0);
	__raw_writel(dev->flags, ssp->mmio_base + SSCR1);
	__raw_writel(dev->psp_flags, ssp->mmio_base + SSPSP);

	return 0;
}