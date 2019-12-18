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
struct wlp {int /*<<< orphan*/  nbmutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  __wlp_neighbors_release (struct wlp*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void wlp_neighbors_release(struct wlp *wlp)
{
	mutex_lock(&wlp->nbmutex);
	__wlp_neighbors_release(wlp);
	mutex_unlock(&wlp->nbmutex);
}