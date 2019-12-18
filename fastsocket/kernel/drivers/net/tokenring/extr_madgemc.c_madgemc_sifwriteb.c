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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIFWRITEB (unsigned short,unsigned short) ; 
 int /*<<< orphan*/  madgemc_setregpage (struct net_device*,int) ; 

__attribute__((used)) static void madgemc_sifwriteb(struct net_device *dev, unsigned short val, unsigned short reg)
{
	if (reg<0x8)
		SIFWRITEB(val, reg);
	else {
		madgemc_setregpage(dev, 1);
		SIFWRITEB(val, reg);
		madgemc_setregpage(dev, 0);
	}
	return;
}