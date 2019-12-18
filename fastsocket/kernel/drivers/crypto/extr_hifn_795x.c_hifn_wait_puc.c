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
struct hifn_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIFN_0_PUCTRL ; 
 int HIFN_PUCTRL_RESET ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int hifn_read_0 (struct hifn_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void hifn_wait_puc(struct hifn_device *dev)
{
	int i;
	u32 ret;

	for (i=10000; i > 0; --i) {
		ret = hifn_read_0(dev, HIFN_0_PUCTRL);
		if (!(ret & HIFN_PUCTRL_RESET))
			break;

		udelay(1);
	}

	if (!i)
		dprintk("%s: Failed to reset PUC unit.\n", dev->name);
}