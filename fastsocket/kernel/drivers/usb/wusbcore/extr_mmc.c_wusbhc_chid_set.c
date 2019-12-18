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
struct wusb_ckhdid {int dummy; } ;
struct wusbhc {int /*<<< orphan*/  pal; int /*<<< orphan*/  mutex; struct wusb_ckhdid chid; scalar_t__ active; } ;
typedef  int /*<<< orphan*/  chid ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ memcmp (struct wusb_ckhdid const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int uwb_radio_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_radio_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wusb_ckhdid_zero ; 

int wusbhc_chid_set(struct wusbhc *wusbhc, const struct wusb_ckhdid *chid)
{
	int result = 0;

	if (memcmp(chid, &wusb_ckhdid_zero, sizeof(chid)) == 0)
		chid = NULL;

	mutex_lock(&wusbhc->mutex);
	if (chid) {
		if (wusbhc->active) {
			mutex_unlock(&wusbhc->mutex);
			return -EBUSY;
		}
		wusbhc->chid = *chid;
	}
	mutex_unlock(&wusbhc->mutex);

	if (chid)
		result = uwb_radio_start(&wusbhc->pal);
	else
		uwb_radio_stop(&wusbhc->pal);
	return result;
}