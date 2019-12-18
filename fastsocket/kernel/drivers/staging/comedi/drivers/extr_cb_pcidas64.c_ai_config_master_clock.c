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
struct TYPE_2__ {int layout; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LAYOUT_4020 128 
 int ai_config_master_clock_4020 (struct comedi_device*,unsigned int*) ; 
 TYPE_1__* board (struct comedi_device*) ; 

__attribute__((used)) static int ai_config_master_clock(struct comedi_device *dev, unsigned int *data)
{

	switch (board(dev)->layout) {
	case LAYOUT_4020:
		return ai_config_master_clock_4020(dev, data);
		break;
	default:
		return -EINVAL;
		break;
	}

	return -EINVAL;
}