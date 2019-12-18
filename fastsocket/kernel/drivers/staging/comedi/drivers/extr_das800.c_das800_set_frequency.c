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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {int /*<<< orphan*/  divisor2; int /*<<< orphan*/  divisor1; } ;

/* Variables and functions */
 scalar_t__ DAS800_8254 ; 
 TYPE_1__* devpriv ; 
 scalar_t__ i8254_load (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int das800_set_frequency(struct comedi_device *dev)
{
	int err = 0;

	if (i8254_load(dev->iobase + DAS800_8254, 0, 1, devpriv->divisor1, 2))
		err++;
	if (i8254_load(dev->iobase + DAS800_8254, 0, 2, devpriv->divisor2, 2))
		err++;
	if (err)
		return -1;

	return 0;
}