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
struct pwm_channel {int index; } ;
struct TYPE_2__ {struct pwm_channel** channel; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int PWM_NCHAN ; 
 TYPE_1__* pwm ; 

__attribute__((used)) static int pwmcheck(struct pwm_channel *ch)
{
	int		index;

	if (!pwm)
		return -ENODEV;
	if (!ch)
		return -EINVAL;
	index = ch->index;
	if (index < 0 || index >= PWM_NCHAN || pwm->channel[index] != ch)
		return -EINVAL;

	return index;
}