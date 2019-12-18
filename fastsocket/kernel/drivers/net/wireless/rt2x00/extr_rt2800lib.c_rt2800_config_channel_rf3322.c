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
typedef  int u8 ;
struct TYPE_2__ {int tx_chain_num; int rx_chain_num; } ;
struct rt2x00_dev {TYPE_1__ default_ant; } ;
struct rf_channel {int rf1; int rf3; } ;
struct ieee80211_conf {int dummy; } ;
struct channel_info {int default_power1; int default_power2; } ;

/* Variables and functions */
 int POWER_BOUND ; 
 int /*<<< orphan*/  RFCSR1_RX0_PD ; 
 int /*<<< orphan*/  RFCSR1_RX1_PD ; 
 int /*<<< orphan*/  RFCSR1_RX2_PD ; 
 int /*<<< orphan*/  RFCSR1_TX0_PD ; 
 int /*<<< orphan*/  RFCSR1_TX1_PD ; 
 int /*<<< orphan*/  RFCSR1_TX2_PD ; 
 int /*<<< orphan*/  rt2800_adjust_freq_offset (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_rfcsr_read (struct rt2x00_dev*,int,int*) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2800_config_channel_rf3322(struct rt2x00_dev *rt2x00dev,
					 struct ieee80211_conf *conf,
					 struct rf_channel *rf,
					 struct channel_info *info)
{
	u8 rfcsr;

	rt2800_rfcsr_write(rt2x00dev, 8, rf->rf1);
	rt2800_rfcsr_write(rt2x00dev, 9, rf->rf3);

	rt2800_rfcsr_write(rt2x00dev, 11, 0x42);
	rt2800_rfcsr_write(rt2x00dev, 12, 0x1c);
	rt2800_rfcsr_write(rt2x00dev, 13, 0x00);

	if (info->default_power1 > POWER_BOUND)
		rt2800_rfcsr_write(rt2x00dev, 47, POWER_BOUND);
	else
		rt2800_rfcsr_write(rt2x00dev, 47, info->default_power1);

	if (info->default_power2 > POWER_BOUND)
		rt2800_rfcsr_write(rt2x00dev, 48, POWER_BOUND);
	else
		rt2800_rfcsr_write(rt2x00dev, 48, info->default_power2);

	rt2800_adjust_freq_offset(rt2x00dev);

	rt2800_rfcsr_read(rt2x00dev, 1, &rfcsr);
	rt2x00_set_field8(&rfcsr, RFCSR1_RX0_PD, 1);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX0_PD, 1);

	if ( rt2x00dev->default_ant.tx_chain_num == 2 )
		rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD, 1);
	else
		rt2x00_set_field8(&rfcsr, RFCSR1_TX1_PD, 0);

	if ( rt2x00dev->default_ant.rx_chain_num == 2 )
		rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD, 1);
	else
		rt2x00_set_field8(&rfcsr, RFCSR1_RX1_PD, 0);

	rt2x00_set_field8(&rfcsr, RFCSR1_RX2_PD, 0);
	rt2x00_set_field8(&rfcsr, RFCSR1_TX2_PD, 0);

	rt2800_rfcsr_write(rt2x00dev, 1, rfcsr);

	rt2800_rfcsr_write(rt2x00dev, 31, 80);
}