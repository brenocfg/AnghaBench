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
struct TYPE_2__ {int /*<<< orphan*/  calibration_source; } ;

/* Variables and functions */
 unsigned int CAL_EN_BIT ; 
 unsigned int CAL_SRC_BITS (int /*<<< orphan*/ ) ; 
 TYPE_1__* devpriv ; 

__attribute__((used)) static inline unsigned int cal_enable_bits(struct comedi_device *dev)
{
	return CAL_EN_BIT | CAL_SRC_BITS(devpriv->calibration_source);
}