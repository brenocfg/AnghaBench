#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct comedi_subdevice {int io_bits; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_ARG ; 
 int /*<<< orphan*/  CALLBACK_FUNC (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int CR_A_IO ; 
 int CR_B_IO ; 
 int CR_CW ; 
 int CR_C_HI_IO ; 
 int CR_C_LO_IO ; 
 int /*<<< orphan*/  _8255_CR ; 

__attribute__((used)) static void do_config(struct comedi_device *dev, struct comedi_subdevice *s)
{
	int config;

	config = CR_CW;
	/* 1 in io_bits indicates output, 1 in config indicates input */
	if (!(s->io_bits & 0x0000ff))
		config |= CR_A_IO;
	if (!(s->io_bits & 0x00ff00))
		config |= CR_B_IO;
	if (!(s->io_bits & 0x0f0000))
		config |= CR_C_LO_IO;
	if (!(s->io_bits & 0xf00000))
		config |= CR_C_HI_IO;
	CALLBACK_FUNC(1, _8255_CR, config, CALLBACK_ARG);
}