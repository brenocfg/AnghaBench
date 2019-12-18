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
struct wusbhc {int /*<<< orphan*/  mutex; } ;
struct wusb_dev {int /*<<< orphan*/  entry_ts; } ;

/* Variables and functions */
 int /*<<< orphan*/  __wusbhc_keep_alive (struct wusbhc*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wusbhc_handle_dn_alive(struct wusbhc *wusbhc, struct wusb_dev *wusb_dev)
{
	mutex_lock(&wusbhc->mutex);
	wusb_dev->entry_ts = jiffies;
	__wusbhc_keep_alive(wusbhc);
	mutex_unlock(&wusbhc->mutex);
}