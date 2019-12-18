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

/* Variables and functions */
 int w1_ds2760_io (struct device*,char*,int,size_t,int /*<<< orphan*/ ) ; 

int w1_ds2760_read(struct device *dev, char *buf, int addr, size_t count)
{
	return w1_ds2760_io(dev, buf, addr, count, 0);
}