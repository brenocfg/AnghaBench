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
typedef  int /*<<< orphan*/  u32 ;
struct rc_dev {struct loopback_dev* priv; } ;
struct loopback_dev {int /*<<< orphan*/  txcarrier; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int loop_set_tx_carrier(struct rc_dev *dev, u32 carrier)
{
	struct loopback_dev *lodev = dev->priv;

	dprintk("setting tx carrier: %u\n", carrier);
	lodev->txcarrier = carrier;
	return 0;
}