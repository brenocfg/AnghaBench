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
struct rc_dev {struct loopback_dev* priv; } ;
struct loopback_dev {int txduty; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 

__attribute__((used)) static int loop_set_tx_duty_cycle(struct rc_dev *dev, u32 duty_cycle)
{
	struct loopback_dev *lodev = dev->priv;

	if (duty_cycle < 1 || duty_cycle > 99) {
		dprintk("invalid duty cycle: %u\n", duty_cycle);
		return -EINVAL;
	}

	dprintk("setting duty cycle: %u\n", duty_cycle);
	lodev->txduty = duty_cycle;
	return 0;
}