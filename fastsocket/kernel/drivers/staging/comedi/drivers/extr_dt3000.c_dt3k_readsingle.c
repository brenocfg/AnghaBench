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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ io_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_READSINGLE ; 
 scalar_t__ DPR_Params (int) ; 
 scalar_t__ DPR_SubSys ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  dt3k_send_cmd (struct comedi_device*,int /*<<< orphan*/ ) ; 
 unsigned int readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static unsigned int dt3k_readsingle(struct comedi_device *dev,
				    unsigned int subsys, unsigned int chan,
				    unsigned int gain)
{
	writew(subsys, devpriv->io_addr + DPR_SubSys);

	writew(chan, devpriv->io_addr + DPR_Params(0));
	writew(gain, devpriv->io_addr + DPR_Params(1));

	dt3k_send_cmd(dev, CMD_READSINGLE);

	return readw(devpriv->io_addr + DPR_Params(2));
}