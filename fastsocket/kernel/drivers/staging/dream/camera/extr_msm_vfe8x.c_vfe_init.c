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
struct msm_vfe_callback {int dummy; } ;

/* Variables and functions */
 int msm_camio_enable (struct platform_device*) ; 
 int vfe_cmd_init (struct msm_vfe_callback*,struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfe_syncdata ; 

__attribute__((used)) static int vfe_init(struct msm_vfe_callback *presp,
	struct platform_device *dev)
{
	int rc = 0;

	rc = vfe_cmd_init(presp, dev, vfe_syncdata);
	if (rc < 0)
		return rc;

	/* Bring up all the required GPIOs and Clocks */
	return msm_camio_enable(dev);
}