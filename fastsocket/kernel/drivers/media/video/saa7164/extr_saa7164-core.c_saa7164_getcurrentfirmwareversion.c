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
typedef  int u32 ;
struct saa7164_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA_DEVICE_VERSION ; 
 int /*<<< orphan*/  dprintk (int,char*,int,int,int,int,int) ; 
 int saa7164_readl (int /*<<< orphan*/ ) ; 

u32 saa7164_getcurrentfirmwareversion(struct saa7164_dev *dev)
{
	u32 reg;

	reg = saa7164_readl(SAA_DEVICE_VERSION);
	dprintk(1, "Device running firmware version %d.%d.%d.%d (0x%x)\n",
		(reg & 0x0000fc00) >> 10,
		(reg & 0x000003e0) >> 5,
		(reg & 0x0000001f),
		(reg & 0xffff0000) >> 16,
		reg);

	return reg;
}