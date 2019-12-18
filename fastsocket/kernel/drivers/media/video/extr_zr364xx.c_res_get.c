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
struct zr364xx_camera {int resources; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _DBG (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int res_get(struct zr364xx_camera *cam)
{
	/* is it free? */
	mutex_lock(&cam->lock);
	if (cam->resources) {
		/* no, someone else uses it */
		mutex_unlock(&cam->lock);
		return 0;
	}
	/* it's free, grab it */
	cam->resources = 1;
	_DBG("res: get\n");
	mutex_unlock(&cam->lock);
	return 1;
}