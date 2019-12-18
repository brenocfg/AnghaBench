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
typedef  int uint32_t ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int,int) ;} ;

/* Variables and functions */
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int,int) ; 

__attribute__((used)) static void win_out2(struct comedi_device *dev, uint32_t data, int reg)
{
	devpriv->stc_writew(dev, data >> 16, reg);
	devpriv->stc_writew(dev, data & 0xffff, reg + 1);
}