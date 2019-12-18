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
struct TYPE_4__ {int config_bits; } ;
struct TYPE_3__ {int* clock; int num_clocks; } ;

/* Variables and functions */
 int CLOCK_DIVISOR_BITS (int) ; 
 int CLOCK_MASK ; 
 int CLOCK_SELECT_BITS (int) ; 
#define  TRIG_ROUND_DOWN 130 
 int TRIG_ROUND_MASK ; 
#define  TRIG_ROUND_NEAREST 129 
#define  TRIG_ROUND_UP 128 
 TYPE_2__* devpriv ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int a2150_get_timing(struct comedi_device *dev, unsigned int *period,
			    int flags)
{
	int lub, glb, temp;
	int lub_divisor_shift, lub_index, glb_divisor_shift, glb_index;
	int i, j;

	/*  initialize greatest lower and least upper bounds */
	lub_divisor_shift = 3;
	lub_index = 0;
	lub = thisboard->clock[lub_index] * (1 << lub_divisor_shift);
	glb_divisor_shift = 0;
	glb_index = thisboard->num_clocks - 1;
	glb = thisboard->clock[glb_index] * (1 << glb_divisor_shift);

	/*  make sure period is in available range */
	if (*period < glb)
		*period = glb;
	if (*period > lub)
		*period = lub;

	/*  we can multiply period by 1, 2, 4, or 8, using (1 << i) */
	for (i = 0; i < 4; i++) {
		/*  there are a maximum of 4 master clocks */
		for (j = 0; j < thisboard->num_clocks; j++) {
			/*  temp is the period in nanosec we are evaluating */
			temp = thisboard->clock[j] * (1 << i);
			/*  if it is the best match yet */
			if (temp < lub && temp >= *period) {
				lub_divisor_shift = i;
				lub_index = j;
				lub = temp;
			}
			if (temp > glb && temp <= *period) {
				glb_divisor_shift = i;
				glb_index = j;
				glb = temp;
			}
		}
	}
	flags &= TRIG_ROUND_MASK;
	switch (flags) {
	case TRIG_ROUND_NEAREST:
	default:
		/*  if least upper bound is better approximation */
		if (lub - *period < *period - glb) {
			*period = lub;
		} else {
			*period = glb;
		}
		break;
	case TRIG_ROUND_UP:
		*period = lub;
		break;
	case TRIG_ROUND_DOWN:
		*period = glb;
		break;
	}

	/*  set clock bits for config register appropriately */
	devpriv->config_bits &= ~CLOCK_MASK;
	if (*period == lub) {
		devpriv->config_bits |=
		    CLOCK_SELECT_BITS(lub_index) |
		    CLOCK_DIVISOR_BITS(lub_divisor_shift);
	} else {
		devpriv->config_bits |=
		    CLOCK_SELECT_BITS(glb_index) |
		    CLOCK_DIVISOR_BITS(glb_divisor_shift);
	}

	return 0;
}