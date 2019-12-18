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
struct TYPE_2__ {int* bits; scalar_t__ hpdi_iobase; } ;

/* Variables and functions */
 TYPE_1__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void hpdi_writel(struct comedi_device *dev, uint32_t bits,
			       unsigned int offset)
{
	writel(bits | priv(dev)->bits[offset / sizeof(uint32_t)],
	       priv(dev)->hpdi_iobase + offset);
}