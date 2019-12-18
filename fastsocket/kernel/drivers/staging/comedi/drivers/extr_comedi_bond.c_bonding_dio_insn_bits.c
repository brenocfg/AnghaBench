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
struct comedi_subdevice {unsigned int state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct BondedDevice {int nchans; int /*<<< orphan*/  subdev; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned int nchans; unsigned int ndevs; struct BondedDevice** devs; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int LSAMPL_BITS ; 
 int comedi_dio_bitfield (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 TYPE_1__* devpriv ; 

__attribute__((used)) static int bonding_dio_insn_bits(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn, unsigned int *data)
{
#define LSAMPL_BITS (sizeof(unsigned int)*8)
	unsigned nchans = LSAMPL_BITS, num_done = 0, i;
	if (insn->n != 2)
		return -EINVAL;

	if (devpriv->nchans < nchans)
		nchans = devpriv->nchans;

	/* The insn data is a mask in data[0] and the new data
	 * in data[1], each channel cooresponding to a bit. */
	for (i = 0; num_done < nchans && i < devpriv->ndevs; ++i) {
		struct BondedDevice *bdev = devpriv->devs[i];
		/* Grab the channel mask and data of only the bits corresponding
		   to this subdevice.. need to shift them to zero position of
		   course. */
		/* Bits corresponding to this subdev. */
		unsigned int subdevMask = ((1 << bdev->nchans) - 1);
		unsigned int writeMask, dataBits;

		/* Argh, we have >= LSAMPL_BITS chans.. take all bits */
		if (bdev->nchans >= LSAMPL_BITS)
			subdevMask = (unsigned int)(-1);

		writeMask = (data[0] >> num_done) & subdevMask;
		dataBits = (data[1] >> num_done) & subdevMask;

		/* Read/Write the new digital lines */
		if (comedi_dio_bitfield(bdev->dev, bdev->subdev, writeMask,
					&dataBits) != 2)
			return -EINVAL;

		/* Make room for the new bits in data[1], the return value */
		data[1] &= ~(subdevMask << num_done);
		/* Put the bits in the return value */
		data[1] |= (dataBits & subdevMask) << num_done;
		/* Save the new bits to the saved state.. */
		s->state = data[1];

		num_done += bdev->nchans;
	}

	return insn->n;
}