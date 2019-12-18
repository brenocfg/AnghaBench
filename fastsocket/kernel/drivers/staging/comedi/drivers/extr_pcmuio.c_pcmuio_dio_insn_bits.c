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
struct comedi_subdevice {unsigned int state; int n_chan; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {unsigned long* iobases; } ;

/* Variables and functions */
 int CHANS_PER_PORT ; 
 int EINVAL ; 
 unsigned char inb (unsigned long) ; 
 int /*<<< orphan*/  outb (unsigned char,unsigned long) ; 
 int /*<<< orphan*/  printk (char*,unsigned int,...) ; 
 TYPE_1__* subpriv ; 

__attribute__((used)) static int pcmuio_dio_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{
	int byte_no;
	if (insn->n != 2)
		return -EINVAL;

	/* NOTE:
	   reading a 0 means this channel was high
	   writine a 0 sets the channel high
	   reading a 1 means this channel was low
	   writing a 1 means set this channel low

	   Therefore everything is always inverted. */

	/* The insn data is a mask in data[0] and the new data
	 * in data[1], each channel cooresponding to a bit. */

#ifdef DAMMIT_ITS_BROKEN
	/* DEBUG */
	printk("write mask: %08x  data: %08x\n", data[0], data[1]);
#endif

	s->state = 0;

	for (byte_no = 0; byte_no < s->n_chan / CHANS_PER_PORT; ++byte_no) {
		/* address of 8-bit port */
		unsigned long ioaddr = subpriv->iobases[byte_no],
		    /* bit offset of port in 32-bit doubleword */
		    offset = byte_no * 8;
		/* this 8-bit port's data */
		unsigned char byte = 0,
		    /* The write mask for this port (if any) */
		    write_mask_byte = (data[0] >> offset) & 0xff,
		    /* The data byte for this port */
		    data_byte = (data[1] >> offset) & 0xff;

		byte = inb(ioaddr);	/* read all 8-bits for this port */

#ifdef DAMMIT_ITS_BROKEN
		/* DEBUG */
		printk
		    ("byte %d wmb %02x db %02x offset %02d io %04x, data_in %02x ",
		     byte_no, (unsigned)write_mask_byte, (unsigned)data_byte,
		     offset, ioaddr, (unsigned)byte);
#endif

		if (write_mask_byte) {
			/* this byte has some write_bits -- so set the output lines */
			byte &= ~write_mask_byte;	/* clear bits for write mask */
			byte |= ~data_byte & write_mask_byte;	/* set to inverted data_byte */
			/* Write out the new digital output state */
			outb(byte, ioaddr);
		}
#ifdef DAMMIT_ITS_BROKEN
		/* DEBUG */
		printk("data_out_byte %02x\n", (unsigned)byte);
#endif
		/* save the digital input lines for this byte.. */
		s->state |= ((unsigned int)byte) << offset;
	}

	/* now return the DIO lines to data[1] - note they came inverted! */
	data[1] = ~s->state;

#ifdef DAMMIT_ITS_BROKEN
	/* DEBUG */
	printk("s->state %08x data_out %08x\n", s->state, data[1]);
#endif

	return 2;
}