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
struct wusbhc {int (* start ) (struct wusbhc*) ;int active; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct wusbhc*) ; 

__attribute__((used)) static int wusbhc_mmc_start(struct wusbhc *wusbhc)
{
	int ret;

	mutex_lock(&wusbhc->mutex);
	ret = wusbhc->start(wusbhc);
	if (ret >= 0)
		wusbhc->active = 1;
	mutex_unlock(&wusbhc->mutex);

	return ret;
}