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
struct wlp {int /*<<< orphan*/  mutex; int /*<<< orphan*/  uuid; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ wlp_wss_uuid_print (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ssize_t wlp_uuid_show(struct wlp *wlp, char *buf)
{
	ssize_t result = 0;

	mutex_lock(&wlp->mutex);
	result = wlp_wss_uuid_print(buf, PAGE_SIZE, &wlp->uuid);
	buf[result++] = '\n';
	mutex_unlock(&wlp->mutex);
	return result;
}