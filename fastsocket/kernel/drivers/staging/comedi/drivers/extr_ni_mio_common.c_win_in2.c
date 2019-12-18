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
struct TYPE_2__ {int (* stc_readw ) (struct comedi_device*,int) ;} ;

/* Variables and functions */
 TYPE_1__* devpriv ; 
 int stub1 (struct comedi_device*,int) ; 
 int stub2 (struct comedi_device*,int) ; 

__attribute__((used)) static uint32_t win_in2(struct comedi_device *dev, int reg)
{
	uint32_t bits;
	bits = devpriv->stc_readw(dev, reg) << 16;
	bits |= devpriv->stc_readw(dev, reg + 1);
	return bits;
}