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
struct TYPE_2__ {int reg_type; int ai_speed; } ;

/* Variables and functions */
 TYPE_1__ boardtype ; 
#define  ni_reg_611x 129 
#define  ni_reg_6143 128 

__attribute__((used)) static unsigned ni_min_ai_scan_period_ns(struct comedi_device *dev,
					 unsigned num_channels)
{
	switch (boardtype.reg_type) {
	case ni_reg_611x:
	case ni_reg_6143:
		/*  simultaneously-sampled inputs */
		return boardtype.ai_speed;
		break;
	default:
		/*  multiplexed inputs */
		break;
	};
	return boardtype.ai_speed * num_channels;
}