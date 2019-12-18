#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct soc_camera_platform_info {int dummy; } ;
struct soc_camera_device {int dummy; } ;
struct TYPE_2__ {struct soc_camera_platform_info* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_soc_camera_control (struct soc_camera_device*) ; 

__attribute__((used)) static struct soc_camera_platform_info *get_info(struct soc_camera_device *icd)
{
	struct platform_device *pdev =
		to_platform_device(to_soc_camera_control(icd));
	return pdev->dev.platform_data;
}