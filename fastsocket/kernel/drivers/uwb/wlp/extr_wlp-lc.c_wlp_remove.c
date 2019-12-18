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
struct wlp {int /*<<< orphan*/ * rc; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * dev_info; int /*<<< orphan*/  eda; int /*<<< orphan*/  uwb_notifs_handler; int /*<<< orphan*/  pal; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_notifs_deregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_pal_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlp_eda_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlp_neighbors_release (struct wlp*) ; 

void wlp_remove(struct wlp *wlp)
{
	wlp_neighbors_release(wlp);
	uwb_pal_unregister(&wlp->pal);
	uwb_notifs_deregister(wlp->rc, &wlp->uwb_notifs_handler);
	wlp_eda_release(&wlp->eda);
	mutex_lock(&wlp->mutex);
	if (wlp->dev_info != NULL)
		kfree(wlp->dev_info);
	mutex_unlock(&wlp->mutex);
	wlp->rc = NULL;
}