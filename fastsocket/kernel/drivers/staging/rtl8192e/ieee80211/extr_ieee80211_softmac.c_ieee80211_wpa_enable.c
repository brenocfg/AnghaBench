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
struct ieee80211_device {int wpa_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,char*) ; 

__attribute__((used)) static int ieee80211_wpa_enable(struct ieee80211_device *ieee, int value)
{
	/* This is called when wpa_supplicant loads and closes the driver
	 * interface. */
	printk("%s WPA\n",value ? "enabling" : "disabling");
	ieee->wpa_enabled = value;
	return 0;
}