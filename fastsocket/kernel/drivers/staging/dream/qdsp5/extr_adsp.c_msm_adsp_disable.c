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
struct msm_adsp_module {int /*<<< orphan*/  lock; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int msm_adsp_disable_locked (struct msm_adsp_module*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

int msm_adsp_disable(struct msm_adsp_module *module)
{
	int rc;
	pr_info("msm_adsp_disable() '%s'\n", module->name);
	mutex_lock(&module->lock);
	rc = msm_adsp_disable_locked(module);
	mutex_unlock(&module->lock);
	return rc;
}