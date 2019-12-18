#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nouveau_pm_level {int dummy; } ;
struct nouveau_pm {TYPE_2__* profile_dc; TYPE_1__* profile_ac; } ;
struct drm_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 struct nouveau_pm* nouveau_pm (struct drm_device*) ; 
 int nouveau_pm_perflvl_get (struct drm_device*,struct nouveau_pm_level*) ; 
 int /*<<< orphan*/  nouveau_pm_perflvl_info (struct nouveau_pm_level*,char*,int) ; 
 struct drm_device* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t
nouveau_pm_get_perflvl(struct device *d, struct device_attribute *a, char *buf)
{
	struct drm_device *dev = pci_get_drvdata(to_pci_dev(d));
	struct nouveau_pm *pm = nouveau_pm(dev);
	struct nouveau_pm_level cur;
	int len = PAGE_SIZE, ret;
	char *ptr = buf;

	snprintf(ptr, len, "profile: %s, %s\nc:",
		 pm->profile_ac->name, pm->profile_dc->name);
	ptr += strlen(buf);
	len -= strlen(buf);

	ret = nouveau_pm_perflvl_get(dev, &cur);
	if (ret == 0)
		nouveau_pm_perflvl_info(&cur, ptr, len);
	return strlen(buf);
}