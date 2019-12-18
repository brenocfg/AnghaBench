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
struct sa1111_dev {scalar_t__ devid; } ;
struct sa1111 {scalar_t__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SA1111_DEVID_SAC ; 
 scalar_t__ SA1111_SKAUD ; 
 int __sa1111_pll_clock (struct sa1111*) ; 
 struct sa1111* sa1111_chip_driver (struct sa1111_dev*) ; 
 int /*<<< orphan*/  sa1111_writel (unsigned int,scalar_t__) ; 

int sa1111_set_audio_rate(struct sa1111_dev *sadev, int rate)
{
	struct sa1111 *sachip = sa1111_chip_driver(sadev);
	unsigned int div;

	if (sadev->devid != SA1111_DEVID_SAC)
		return -EINVAL;

	div = (__sa1111_pll_clock(sachip) / 256 + rate / 2) / rate;
	if (div == 0)
		div = 1;
	if (div > 128)
		div = 128;

	sa1111_writel(div - 1, sachip->base + SA1111_SKAUD);

	return 0;
}