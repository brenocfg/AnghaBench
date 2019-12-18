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
struct TYPE_2__ {int int_thermal_type; } ;
struct radeon_device {TYPE_1__ pm; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
#define  THERMAL_TYPE_EVERGREEN 133 
#define  THERMAL_TYPE_NI 132 
#define  THERMAL_TYPE_RV6XX 131 
#define  THERMAL_TYPE_RV770 130 
#define  THERMAL_TYPE_SI 129 
#define  THERMAL_TYPE_SUMO 128 
 int evergreen_get_temp (struct radeon_device*) ; 
 struct drm_device* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int rv6xx_get_temp (struct radeon_device*) ; 
 int rv770_get_temp (struct radeon_device*) ; 
 int si_get_temp (struct radeon_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int sumo_get_temp (struct radeon_device*) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t radeon_hwmon_show_temp(struct device *dev,
				      struct device_attribute *attr,
				      char *buf)
{
	struct drm_device *ddev = pci_get_drvdata(to_pci_dev(dev));
	struct radeon_device *rdev = ddev->dev_private;
	int temp;

	switch (rdev->pm.int_thermal_type) {
	case THERMAL_TYPE_RV6XX:
		temp = rv6xx_get_temp(rdev);
		break;
	case THERMAL_TYPE_RV770:
		temp = rv770_get_temp(rdev);
		break;
	case THERMAL_TYPE_EVERGREEN:
	case THERMAL_TYPE_NI:
		temp = evergreen_get_temp(rdev);
		break;
	case THERMAL_TYPE_SUMO:
		temp = sumo_get_temp(rdev);
		break;
	case THERMAL_TYPE_SI:
		temp = si_get_temp(rdev);
		break;
	default:
		temp = 0;
		break;
	}

	return snprintf(buf, PAGE_SIZE, "%d\n", temp);
}