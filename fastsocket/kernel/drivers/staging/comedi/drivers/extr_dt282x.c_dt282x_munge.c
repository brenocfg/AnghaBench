#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_4__ {int adbits; } ;
struct TYPE_3__ {scalar_t__ ad_2scomp; } ;

/* Variables and functions */
 TYPE_2__ boardtype ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* devpriv ; 

__attribute__((used)) static void dt282x_munge(struct comedi_device *dev, short *buf,
			 unsigned int nbytes)
{
	unsigned int i;
	unsigned short mask = (1 << boardtype.adbits) - 1;
	unsigned short sign = 1 << (boardtype.adbits - 1);
	int n;

	if (devpriv->ad_2scomp) {
		sign = 1 << (boardtype.adbits - 1);
	} else {
		sign = 0;
	}

	if (nbytes % 2)
		comedi_error(dev, "bug! odd number of bytes from dma xfer");
	n = nbytes / 2;
	for (i = 0; i < n; i++) {
		buf[i] = (buf[i] & mask) ^ sign;
	}
}