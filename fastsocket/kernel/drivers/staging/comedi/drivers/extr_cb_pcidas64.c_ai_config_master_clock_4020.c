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
struct TYPE_3__ {unsigned int divisor; unsigned int chanspec; } ;
struct TYPE_4__ {TYPE_1__ ext_clock; } ;

/* Variables and functions */
#define  COMEDI_EV_SCAN_BEGIN 128 
 int EAGAIN ; 
 int EINVAL ; 
 TYPE_2__* priv (struct comedi_device*) ; 

__attribute__((used)) static int ai_config_master_clock_4020(struct comedi_device *dev,
				       unsigned int *data)
{
	unsigned int divisor = data[4];
	int retval = 0;

	if (divisor < 2) {
		divisor = 2;
		retval = -EAGAIN;
	}

	switch (data[1]) {
	case COMEDI_EV_SCAN_BEGIN:
		priv(dev)->ext_clock.divisor = divisor;
		priv(dev)->ext_clock.chanspec = data[2];
		break;
	default:
		return -EINVAL;
		break;
	}

	data[4] = divisor;

	return retval ? retval : 5;
}