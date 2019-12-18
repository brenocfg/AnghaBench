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
struct TYPE_2__ {scalar_t__ ai_cmd_running; scalar_t__ base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC1_ERPS1 ; 
 int /*<<< orphan*/  MC_DISABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ P_IER ; 
 int /*<<< orphan*/  P_MC1 ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s626_ai_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	/*  Stop RPS program in case it is currently running. */
	MC_DISABLE(P_MC1, MC1_ERPS1);

	/* disable master interrupt */
	writel(0, devpriv->base_addr + P_IER);

	devpriv->ai_cmd_running = 0;

	return 0;
}