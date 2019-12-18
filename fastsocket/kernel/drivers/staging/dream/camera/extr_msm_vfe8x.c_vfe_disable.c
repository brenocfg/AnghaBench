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
struct camera_enable_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_camio_disable (struct platform_device*) ; 
 int /*<<< orphan*/  vfe_stop () ; 

__attribute__((used)) static int vfe_disable(struct camera_enable_cmd *enable,
	struct platform_device *dev)
{
	int rc = 0;

	vfe_stop();

	msm_camio_disable(dev);
	return rc;
}