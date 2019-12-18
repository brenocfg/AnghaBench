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
 int /*<<< orphan*/  CMD_CONFIG ; 
 scalar_t__ DPR_Params (int) ; 
 scalar_t__ DPR_SubSys ; 
 int SUBS_DOUT ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  dt3k_send_cmd (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void dt3k_dio_config(struct comedi_device *dev, int bits)
{
	/* XXX */
	writew(SUBS_DOUT, devpriv->io_addr + DPR_SubSys);

	writew(bits, devpriv->io_addr + DPR_Params(0));
#if 0
	/* don't know */
	writew(0, devpriv->io_addr + DPR_Params(1));
	writew(0, devpriv->io_addr + DPR_Params(2));
#endif

	dt3k_send_cmd(dev, CMD_CONFIG);
}