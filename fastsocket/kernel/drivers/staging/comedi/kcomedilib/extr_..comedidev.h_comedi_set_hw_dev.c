#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device {int dummy; } ;
struct comedi_device {struct device* hw_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct device* get_device (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static inline void comedi_set_hw_dev(struct comedi_device *dev,
				     struct device *hw_dev)
{
	if (dev->hw_dev)
		put_device(dev->hw_dev);

	dev->hw_dev = hw_dev;
	if (dev->hw_dev) {
		dev->hw_dev = get_device(dev->hw_dev);
		BUG_ON(dev->hw_dev == NULL);
	}
}