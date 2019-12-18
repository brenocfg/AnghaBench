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
struct uvd {int uvd_used; int /*<<< orphan*/ * dev; int /*<<< orphan*/  lock; } ;
struct usbvideo {int num_cameras; int /*<<< orphan*/  lock; struct uvd* cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usbvideo_find_struct(struct usbvideo *cams)
{
	int u, rv = -1;

	if (cams == NULL) {
		err("No usbvideo handle?");
		return -1;
	}
	mutex_lock(&cams->lock);
	for (u = 0; u < cams->num_cameras; u++) {
		struct uvd *uvd = &cams->cam[u];
		if (!uvd->uvd_used) /* This one is free */
		{
			uvd->uvd_used = 1;	/* In use now */
			mutex_init(&uvd->lock);	/* to 1 == available */
			uvd->dev = NULL;
			rv = u;
			break;
		}
	}
	mutex_unlock(&cams->lock);
	return rv;
}