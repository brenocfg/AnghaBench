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
struct TYPE_2__ {scalar_t__ io_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STOP ; 
 scalar_t__ DPR_Int_Mask ; 
 scalar_t__ DPR_SubSys ; 
 int /*<<< orphan*/  SUBS_AI ; 
 TYPE_1__* devpriv ; 
 int dt3k_send_cmd (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dt3k_ai_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	int ret;

	writew(SUBS_AI, devpriv->io_addr + DPR_SubSys);
	ret = dt3k_send_cmd(dev, CMD_STOP);

	writew(0, devpriv->io_addr + DPR_Int_Mask);

	return 0;
}