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
typedef  int /*<<< orphan*/  uint8_t ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {unsigned long s5933_config; } ;

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_MCSR_NVCMD ; 
 scalar_t__ AMCC_OP_REG_MCSR_NVDATA ; 
 int ETIMEDOUT ; 
 unsigned int MCSR_NV_ENABLE ; 
 unsigned int MCSR_NV_LOAD_HIGH_ADDR ; 
 unsigned int MCSR_NV_LOAD_LOW_ADDR ; 
 unsigned int MCSR_NV_READ ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 scalar_t__ wait_for_nvram_ready (unsigned long) ; 

__attribute__((used)) static int nvram_read(struct comedi_device *dev, unsigned int address,
		      uint8_t * data)
{
	unsigned long iobase = devpriv->s5933_config;

	if (wait_for_nvram_ready(iobase) < 0)
		return -ETIMEDOUT;

	outb(MCSR_NV_ENABLE | MCSR_NV_LOAD_LOW_ADDR,
	     iobase + AMCC_OP_REG_MCSR_NVCMD);
	outb(address & 0xff, iobase + AMCC_OP_REG_MCSR_NVDATA);
	outb(MCSR_NV_ENABLE | MCSR_NV_LOAD_HIGH_ADDR,
	     iobase + AMCC_OP_REG_MCSR_NVCMD);
	outb((address >> 8) & 0xff, iobase + AMCC_OP_REG_MCSR_NVDATA);
	outb(MCSR_NV_ENABLE | MCSR_NV_READ, iobase + AMCC_OP_REG_MCSR_NVCMD);

	if (wait_for_nvram_ready(iobase) < 0)
		return -ETIMEDOUT;

	*data = inb(iobase + AMCC_OP_REG_MCSR_NVDATA);

	return 0;
}