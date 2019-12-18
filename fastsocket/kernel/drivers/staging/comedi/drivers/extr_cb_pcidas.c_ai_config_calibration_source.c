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
struct TYPE_2__ {unsigned int calibration_source; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 

__attribute__((used)) static int ai_config_calibration_source(struct comedi_device *dev,
					unsigned int *data)
{
	static const int num_calibration_sources = 8;
	unsigned int source = data[1];

	if (source >= num_calibration_sources) {
		printk("invalid calibration source: %i\n", source);
		return -EINVAL;
	}

	devpriv->calibration_source = source;

	return 2;
}