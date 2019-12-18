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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  config_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_BITS (int) ; 
 int /*<<< orphan*/  CHANNEL_MASK ; 
 TYPE_1__* devpriv ; 

__attribute__((used)) static int a2150_set_chanlist(struct comedi_device *dev,
			      unsigned int start_channel,
			      unsigned int num_channels)
{
	if (start_channel + num_channels > 4)
		return -1;

	devpriv->config_bits &= ~CHANNEL_MASK;

	switch (num_channels) {
	case 1:
		devpriv->config_bits |= CHANNEL_BITS(0x4 | start_channel);
		break;
	case 2:
		if (start_channel == 0) {
			devpriv->config_bits |= CHANNEL_BITS(0x2);
		} else if (start_channel == 2) {
			devpriv->config_bits |= CHANNEL_BITS(0x3);
		} else {
			return -1;
		}
		break;
	case 4:
		devpriv->config_bits |= CHANNEL_BITS(0x1);
		break;
	default:
		return -1;
		break;
	}

	return 0;
}