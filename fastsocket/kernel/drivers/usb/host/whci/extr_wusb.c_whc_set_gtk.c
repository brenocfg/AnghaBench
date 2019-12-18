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
typedef  int /*<<< orphan*/  u32 ;
struct wusbhc {int dummy; } ;
struct whc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  n_devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int whc_set_key (struct whc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t,int) ; 
 struct whc* wusbhc_to_whc (struct wusbhc*) ; 

int whc_set_gtk(struct wusbhc *wusbhc, u32 tkid,
		const void *gtk, size_t key_size)
{
	struct whc *whc = wusbhc_to_whc(wusbhc);
	int ret;

	mutex_lock(&whc->mutex);

	ret = whc_set_key(whc, whc->n_devices, tkid, gtk, key_size, true);

	mutex_unlock(&whc->mutex);

	return ret;
}