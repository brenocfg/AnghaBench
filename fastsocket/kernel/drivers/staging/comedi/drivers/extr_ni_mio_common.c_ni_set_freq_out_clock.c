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
struct TYPE_2__ {int /*<<< orphan*/  clock_and_fout; int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Clock_and_FOUT_Register ; 
 int EINVAL ; 
 int /*<<< orphan*/  FOUT_Timebase_Select ; 
#define  NI_FREQ_OUT_TIMEBASE_1_DIV_2_CLOCK_SRC 129 
#define  NI_FREQ_OUT_TIMEBASE_2_CLOCK_SRC 128 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_set_freq_out_clock(struct comedi_device *dev,
				 unsigned int clock_source)
{
	switch (clock_source) {
	case NI_FREQ_OUT_TIMEBASE_1_DIV_2_CLOCK_SRC:
		devpriv->clock_and_fout &= ~FOUT_Timebase_Select;
		break;
	case NI_FREQ_OUT_TIMEBASE_2_CLOCK_SRC:
		devpriv->clock_and_fout |= FOUT_Timebase_Select;
		break;
	default:
		return -EINVAL;
	}
	devpriv->stc_writew(dev, devpriv->clock_and_fout,
			    Clock_and_FOUT_Register);
	return 3;
}