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

/* Variables and functions */
 scalar_t__ RPCROUTER_MAX_REMOTE_SERVERS ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_rpcrouter_class ; 
 int /*<<< orphan*/  msm_rpcrouter_devno ; 
 int /*<<< orphan*/  rpcrouter_cdev ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,scalar_t__) ; 

void msm_rpcrouter_exit_devices(void)
{
	cdev_del(&rpcrouter_cdev);
	device_destroy(msm_rpcrouter_class, msm_rpcrouter_devno);
	unregister_chrdev_region(msm_rpcrouter_devno,
				 RPCROUTER_MAX_REMOTE_SERVERS + 1);
	class_destroy(msm_rpcrouter_class);
}