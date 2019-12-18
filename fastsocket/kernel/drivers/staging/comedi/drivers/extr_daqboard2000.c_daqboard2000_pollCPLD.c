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
struct TYPE_2__ {scalar_t__ daq; } ;

/* Variables and functions */
 TYPE_1__* devpriv ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int daqboard2000_pollCPLD(struct comedi_device *dev, int mask)
{
	int result = 0;
	int i;
	int cpld;

	/* timeout after 50 tries -> 5ms */
	for (i = 0; i < 50; i++) {
		cpld = readw(devpriv->daq + 0x1000);
		if ((cpld & mask) == mask) {
			result = 1;
			break;
		}
		udelay(100);
	}
	udelay(5);
	return result;
}