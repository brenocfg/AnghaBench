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
struct TYPE_4__ {int layout; } ;
struct TYPE_3__ {unsigned int* caldac_state; } ;

/* Variables and functions */
#define  LAYOUT_4020 130 
#define  LAYOUT_60XX 129 
#define  LAYOUT_64XX 128 
 TYPE_2__* board (struct comedi_device*) ; 
 int /*<<< orphan*/  caldac_8800_write (struct comedi_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  caldac_i2c_write (struct comedi_device*,unsigned int,unsigned int) ; 
 TYPE_1__* priv (struct comedi_device*) ; 

__attribute__((used)) static void caldac_write(struct comedi_device *dev, unsigned int channel,
			 unsigned int value)
{
	priv(dev)->caldac_state[channel] = value;

	switch (board(dev)->layout) {
	case LAYOUT_60XX:
	case LAYOUT_64XX:
		caldac_8800_write(dev, channel, value);
		break;
	case LAYOUT_4020:
		caldac_i2c_write(dev, channel, value);
		break;
	default:
		break;
	}
}