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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ hpdi_iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOARD_CONTROL_REG ; 
 scalar_t__ INTERRUPT_CONTROL_REG ; 
 int /*<<< orphan*/  abort_dma (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpdi_writel (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int hpdi_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	hpdi_writel(dev, 0, BOARD_CONTROL_REG);

	writel(0, priv(dev)->hpdi_iobase + INTERRUPT_CONTROL_REG);

	abort_dma(dev, 0);

	return 0;
}