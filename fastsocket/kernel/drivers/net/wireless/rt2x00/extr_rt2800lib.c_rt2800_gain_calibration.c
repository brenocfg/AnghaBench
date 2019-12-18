#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rt2x00_dev {int /*<<< orphan*/  tx_power; TYPE_3__* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  chan; } ;
struct TYPE_5__ {TYPE_1__ chandef; } ;
struct TYPE_6__ {TYPE_2__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt2800_config_txpower (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rt2800_gain_calibration(struct rt2x00_dev *rt2x00dev)
{
	rt2800_config_txpower(rt2x00dev, rt2x00dev->hw->conf.chandef.chan,
			      rt2x00dev->tx_power);
}