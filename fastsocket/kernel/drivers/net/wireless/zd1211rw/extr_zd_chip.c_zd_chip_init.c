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
struct zd_chip {int /*<<< orphan*/  rf; int /*<<< orphan*/  usb; int /*<<< orphan*/  mutex; } ;
struct usb_interface {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct zd_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_rf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_usb_init (int /*<<< orphan*/ *,struct ieee80211_hw*,struct usb_interface*) ; 

void zd_chip_init(struct zd_chip *chip,
	         struct ieee80211_hw *hw,
		 struct usb_interface *intf)
{
	memset(chip, 0, sizeof(*chip));
	mutex_init(&chip->mutex);
	zd_usb_init(&chip->usb, hw, intf);
	zd_rf_init(&chip->rf);
}