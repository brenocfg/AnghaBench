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
struct msm_sync {int dummy; } ;
struct msm_device {struct msm_sync* sync; int /*<<< orphan*/  opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_devno ; 
 int /*<<< orphan*/  msm_fops_config ; 
 int /*<<< orphan*/  msm_fops_control ; 
 int /*<<< orphan*/  msm_fops_frame ; 
 int msm_setup_cdev (struct msm_device*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_tear_down_cdev (struct msm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int msm_device_init(struct msm_device *pmsm,
		struct msm_sync *sync,
		int node)
{
	int dev_num = 3 * node;
	int rc = msm_setup_cdev(pmsm, node,
		MKDEV(MAJOR(msm_devno), dev_num),
		"control", &msm_fops_control);
	if (rc < 0) {
		pr_err("error creating control node: %d\n", rc);
		return rc;
	}

	rc = msm_setup_cdev(pmsm + 1, node,
		MKDEV(MAJOR(msm_devno), dev_num + 1),
		"config", &msm_fops_config);
	if (rc < 0) {
		pr_err("error creating config node: %d\n", rc);
		msm_tear_down_cdev(pmsm, MKDEV(MAJOR(msm_devno),
				dev_num));
		return rc;
	}

	rc = msm_setup_cdev(pmsm + 2, node,
		MKDEV(MAJOR(msm_devno), dev_num + 2),
		"frame", &msm_fops_frame);
	if (rc < 0) {
		pr_err("error creating frame node: %d\n", rc);
		msm_tear_down_cdev(pmsm,
			MKDEV(MAJOR(msm_devno), dev_num));
		msm_tear_down_cdev(pmsm + 1,
			MKDEV(MAJOR(msm_devno), dev_num + 1));
		return rc;
	}

	atomic_set(&pmsm[0].opened, 0);
	atomic_set(&pmsm[1].opened, 0);
	atomic_set(&pmsm[2].opened, 0);

	pmsm[0].sync = sync;
	pmsm[1].sync = sync;
	pmsm[2].sync = sync;

	return rc;
}