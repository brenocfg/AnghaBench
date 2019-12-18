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
struct TYPE_2__ {scalar_t__ layout; } ;

/* Variables and functions */
 unsigned short ADC_SE_DIFF_BIT ; 
 scalar_t__ LAYOUT_60XX ; 
 scalar_t__ LAYOUT_64XX ; 
 TYPE_1__* board (struct comedi_device*) ; 

__attribute__((used)) static inline unsigned short se_diff_bit_6xxx(struct comedi_device *dev,
					      int use_differential)
{
	if ((board(dev)->layout == LAYOUT_64XX && !use_differential) ||
	    (board(dev)->layout == LAYOUT_60XX && use_differential))
		return ADC_SE_DIFF_BIT;
	else
		return 0;
}