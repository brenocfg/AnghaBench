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
struct zd_chip {int /*<<< orphan*/  mutex; int /*<<< orphan*/  usb; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_tx_watchdog_enable (int /*<<< orphan*/ *) ; 
 int zd_usb_enable_rx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_usb_enable_tx (int /*<<< orphan*/ *) ; 

int zd_chip_enable_rxtx(struct zd_chip *chip)
{
	int r;

	mutex_lock(&chip->mutex);
	zd_usb_enable_tx(&chip->usb);
	r = zd_usb_enable_rx(&chip->usb);
	zd_tx_watchdog_enable(&chip->usb);
	mutex_unlock(&chip->mutex);
	return r;
}