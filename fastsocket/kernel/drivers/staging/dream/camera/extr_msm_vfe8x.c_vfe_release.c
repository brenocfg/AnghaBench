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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_camio_disable (struct platform_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfe_cmd_release (struct platform_device*) ; 
 int /*<<< orphan*/  vfe_lock ; 
 int /*<<< orphan*/ * vfe_syncdata ; 

__attribute__((used)) static void vfe_release(struct platform_device *dev)
{
	msm_camio_disable(dev);
	vfe_cmd_release(dev);

	mutex_lock(&vfe_lock);
	vfe_syncdata = NULL;
	mutex_unlock(&vfe_lock);
}