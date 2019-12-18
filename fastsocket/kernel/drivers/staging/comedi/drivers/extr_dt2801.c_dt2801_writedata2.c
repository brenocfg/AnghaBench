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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int dt2801_writedata (struct comedi_device*,unsigned int) ; 

__attribute__((used)) static int dt2801_writedata2(struct comedi_device *dev, unsigned int data)
{
	int ret;

	ret = dt2801_writedata(dev, data & 0xff);
	if (ret < 0)
		return ret;
	ret = dt2801_writedata(dev, (data >> 8));
	if (ret < 0)
		return ret;

	return 0;
}