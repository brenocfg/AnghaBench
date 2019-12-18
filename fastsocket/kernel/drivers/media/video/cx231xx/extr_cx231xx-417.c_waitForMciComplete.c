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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,int) ; 
 int /*<<< orphan*/  getITVCReg (struct cx231xx*,int,int*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int waitForMciComplete(struct cx231xx *dev)
{
	u32 gpio;
	u32 gpio_driection = 0;
	u8 count = 0;
	getITVCReg(dev, gpio_driection, &gpio);

	while (!(gpio&0x020000)) {
		msleep(10);

		getITVCReg(dev, gpio_driection, &gpio);

		if (count++ > 100) {
			dprintk(3, "ERROR: Timeout - gpio=%x\n", gpio);
			return -1;
		}
	}
	return 0;
}