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
struct TYPE_4__ {int /*<<< orphan*/  chanBipolar; } ;
struct TYPE_3__ {unsigned int range10Start; unsigned int rangeUniStart; } ;

/* Variables and functions */
#define  AREF_COMMON 131 
#define  AREF_DIFF 130 
#define  AREF_GROUND 129 
#define  AREF_OTHER 128 
 int /*<<< orphan*/  CHAN_ARRAY_CLEAR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CHAN_ARRAY_SET (int /*<<< orphan*/ ,int) ; 
 unsigned int CR_AREF (unsigned int) ; 
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_RANGE (unsigned int) ; 
 TYPE_2__* devpriv ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static unsigned short rtdConvertChanGain(struct comedi_device *dev,
					 unsigned int comediChan, int chanIndex)
{				/* index in channel list */
	unsigned int chan, range, aref;
	unsigned short r = 0;

	chan = CR_CHAN(comediChan);
	range = CR_RANGE(comediChan);
	aref = CR_AREF(comediChan);

	r |= chan & 0xf;

	/* Note: we also setup the channel list bipolar flag array */
	if (range < thisboard->range10Start) {	/* first batch are +-5 */
		r |= 0x000;	/* +-5 range */
		r |= (range & 0x7) << 4;	/* gain */
		CHAN_ARRAY_SET(devpriv->chanBipolar, chanIndex);
	} else if (range < thisboard->rangeUniStart) {	/* second batch are +-10 */
		r |= 0x100;	/* +-10 range */
		r |= ((range - thisboard->range10Start) & 0x7) << 4;	/* gain */
		CHAN_ARRAY_SET(devpriv->chanBipolar, chanIndex);
	} else {		/* last batch is +10 */
		r |= 0x200;	/* +10 range */
		r |= ((range - thisboard->rangeUniStart) & 0x7) << 4;	/* gain */
		CHAN_ARRAY_CLEAR(devpriv->chanBipolar, chanIndex);
	}

	switch (aref) {
	case AREF_GROUND:	/* on-board ground */
		break;

	case AREF_COMMON:
		r |= 0x80;	/* ref external analog common */
		break;

	case AREF_DIFF:
		r |= 0x400;	/* differential inputs */
		break;

	case AREF_OTHER:	/* ??? */
		break;
	}
	/*printk ("chan=%d r=%d a=%d -> 0x%x\n",
	   chan, range, aref, r); */
	return r;
}