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
typedef  int u8 ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSCDR ; 
 int /*<<< orphan*/  CSCIR ; 
 int EINVAL ; 
 int PADR ; 
 int PBDR ; 
 int PCDR ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dnp_dio_insn_bits(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_insn *insn, unsigned int *data)
{

	if (insn->n != 2)
		return -EINVAL;	/* insn uses data[0] and data[1]     */

	/* The insn data is a mask in data[0] and the new data in data[1], each    */
	/* channel cooresponding to a bit.                                         */

	/* Ports A and B are straight forward: each bit corresponds to an output   */
	/* pin with the same order. Port C is different: bits 0...3 correspond to  */
	/* bits 4...7 of the output register (PCDR).                               */

	if (data[0]) {

		outb(PADR, CSCIR);
		outb((inb(CSCDR)
		      & ~(u8) (data[0] & 0x0000FF))
		     | (u8) (data[1] & 0x0000FF), CSCDR);

		outb(PBDR, CSCIR);
		outb((inb(CSCDR)
		      & ~(u8) ((data[0] & 0x00FF00) >> 8))
		     | (u8) ((data[1] & 0x00FF00) >> 8), CSCDR);

		outb(PCDR, CSCIR);
		outb((inb(CSCDR)
		      & ~(u8) ((data[0] & 0x0F0000) >> 12))
		     | (u8) ((data[1] & 0x0F0000) >> 12), CSCDR);
	}

	/* on return, data[1] contains the value of the digital input lines.       */
	outb(PADR, CSCIR);
	data[0] = inb(CSCDR);
	outb(PBDR, CSCIR);
	data[0] += inb(CSCDR) << 8;
	outb(PCDR, CSCIR);
	data[0] += ((inb(CSCDR) & 0xF0) << 12);

	return 2;

}