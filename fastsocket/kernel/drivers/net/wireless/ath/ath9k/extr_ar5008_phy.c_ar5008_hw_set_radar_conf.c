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
struct ath_hw_radar_conf {int fir_power; int radar_rssi; int pulse_height; int pulse_rssi; int pulse_inband; int pulse_maxlen; int pulse_inband_step; int radar_inband; } ;
struct ath_hw {struct ath_hw_radar_conf radar_conf; } ;

/* Variables and functions */

__attribute__((used)) static void ar5008_hw_set_radar_conf(struct ath_hw *ah)
{
	struct ath_hw_radar_conf *conf = &ah->radar_conf;

	conf->fir_power = -33;
	conf->radar_rssi = 20;
	conf->pulse_height = 10;
	conf->pulse_rssi = 24;
	conf->pulse_inband = 15;
	conf->pulse_maxlen = 255;
	conf->pulse_inband_step = 12;
	conf->radar_inband = 8;
}