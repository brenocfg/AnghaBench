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
typedef  int u8 ;
struct apm_power_info {int battery_life; int time; int ac_line_status; int battery_flag; int /*<<< orphan*/  battery_status; scalar_t__ units; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_CHANNEL_BACKUP ; 
 int /*<<< orphan*/  ADC_CHANNEL_BATTERY ; 
 int /*<<< orphan*/  ADC_CHANNEL_CHARGE ; 
 int APM_AC_OFFLINE ; 
 int APM_AC_ONLINE ; 
 int /*<<< orphan*/  APM_BATTERY_STATUS_CHARGING ; 
 int /*<<< orphan*/  APM_BATTERY_STATUS_CRITICAL ; 
 int /*<<< orphan*/  APM_BATTERY_STATUS_HIGH ; 
 int /*<<< orphan*/  APM_BATTERY_STATUS_LOW ; 
 int /*<<< orphan*/  APM_BATTERY_STATUS_NOT_PRESENT ; 
 int APM_CRITICAL ; 
 int APM_LOW ; 
 int HP680_BATTERY_AC_ON ; 
 int HP680_BATTERY_MAX ; 
 int HP680_BATTERY_MIN ; 
 int /*<<< orphan*/  PGDR ; 
 int PGDR_MAIN_BATTERY_OUT ; 
 int adc_single (int /*<<< orphan*/ ) ; 
 int ctrl_inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hp6x0_apm_get_power_status(struct apm_power_info *info)
{
	int battery, backup, charging, percentage;
	u8 pgdr;

	battery		= adc_single(ADC_CHANNEL_BATTERY);
	backup		= adc_single(ADC_CHANNEL_BACKUP);
	charging	= adc_single(ADC_CHANNEL_CHARGE);

	percentage = 100 * (battery - HP680_BATTERY_MIN) /
			   (HP680_BATTERY_MAX - HP680_BATTERY_MIN);

	/* % of full battery */
	info->battery_life = percentage;

	/* We want our estimates in minutes */
	info->units = 0;

	/* Extremely(!!) rough estimate, we will replace this with a datalist later on */
	info->time = (2 * battery);

	info->ac_line_status = (battery > HP680_BATTERY_AC_ON) ?
			 APM_AC_ONLINE : APM_AC_OFFLINE;

	pgdr = ctrl_inb(PGDR);
	if (pgdr & PGDR_MAIN_BATTERY_OUT) {
		info->battery_status	= APM_BATTERY_STATUS_NOT_PRESENT;
		info->battery_flag	= 0x80;
	} else if (charging < 8) {
		info->battery_status	= APM_BATTERY_STATUS_CHARGING;
		info->battery_flag	= 0x08;
		info->ac_line_status	= 0x01;
	} else if (percentage <= APM_CRITICAL) {
		info->battery_status	= APM_BATTERY_STATUS_CRITICAL;
		info->battery_flag	= 0x04;
	} else if (percentage <= APM_LOW) {
		info->battery_status	= APM_BATTERY_STATUS_LOW;
		info->battery_flag	= 0x02;
	} else {
		info->battery_status	= APM_BATTERY_STATUS_HIGH;
		info->battery_flag	= 0x01;
	}
}