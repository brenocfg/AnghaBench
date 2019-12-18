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
typedef  int /*<<< orphan*/  u8 ;
struct wusbhc {int (* mmcie_add ) (struct wusbhc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct wuie_hdr*) ;int /*<<< orphan*/  mmcie_mutex; struct wuie_hdr** mmcie; int /*<<< orphan*/  mmcies_max; int /*<<< orphan*/  dev; } ;
struct wuie_hdr {int bIEIdentifier; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOSYS ; 
#define  WUIE_ID_HOST_INFO 129 
#define  WUIE_ID_ISOCH_DISCARD 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct wusbhc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct wuie_hdr*) ; 

int wusbhc_mmcie_set(struct wusbhc *wusbhc, u8 interval, u8 repeat_cnt,
		     struct wuie_hdr *wuie)
{
	int result = -ENOBUFS;
	unsigned handle, itr;

	/* Search a handle, taking into account the ordering */
	mutex_lock(&wusbhc->mmcie_mutex);
	switch (wuie->bIEIdentifier) {
	case WUIE_ID_HOST_INFO:
		/* Always last */
		handle = wusbhc->mmcies_max - 1;
		break;
	case WUIE_ID_ISOCH_DISCARD:
		dev_err(wusbhc->dev, "Special ordering case for WUIE ID 0x%x "
			"unimplemented\n", wuie->bIEIdentifier);
		result = -ENOSYS;
		goto error_unlock;
	default:
		/* search for it or find the last empty slot */
		handle = ~0;
		for (itr = 0; itr < wusbhc->mmcies_max - 1; itr++) {
			if (wusbhc->mmcie[itr] == wuie) {
				handle = itr;
				break;
			}
			if (wusbhc->mmcie[itr] == NULL)
				handle = itr;
		}
		if (handle == ~0)
			goto error_unlock;
	}
	result = (wusbhc->mmcie_add)(wusbhc, interval, repeat_cnt, handle,
				     wuie);
	if (result >= 0)
		wusbhc->mmcie[handle] = wuie;
error_unlock:
	mutex_unlock(&wusbhc->mmcie_mutex);
	return result;
}