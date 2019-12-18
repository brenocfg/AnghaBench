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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 short fake_flatline (struct comedi_device*,unsigned int,unsigned long) ; 
 short fake_sawtooth (struct comedi_device*,unsigned int,unsigned long) ; 
 short fake_squarewave (struct comedi_device*,unsigned int,unsigned long) ; 

__attribute__((used)) static short fake_waveform(struct comedi_device *dev, unsigned int channel,
			   unsigned int range, unsigned long current_time)
{
	enum {
		SAWTOOTH_CHAN,
		SQUARE_CHAN,
	};
	switch (channel) {
	case SAWTOOTH_CHAN:
		return fake_sawtooth(dev, range, current_time);
		break;
	case SQUARE_CHAN:
		return fake_squarewave(dev, range, current_time);
		break;
	default:
		break;
	}

	return fake_flatline(dev, range, current_time);
}