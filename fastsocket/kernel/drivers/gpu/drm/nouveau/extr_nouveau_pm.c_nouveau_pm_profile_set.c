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
struct nouveau_pm_profile {int dummy; } ;
struct nouveau_pm {struct nouveau_pm_profile* profile_dc; struct nouveau_pm_profile* profile_ac; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  string ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int nouveau_perflvl_wr ; 
 struct nouveau_pm* nouveau_pm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_pm_trigger (struct drm_device*) ; 
 struct nouveau_pm_profile* profile_find (struct drm_device*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
nouveau_pm_profile_set(struct drm_device *dev, const char *profile)
{
	struct nouveau_pm *pm = nouveau_pm(dev);
	struct nouveau_pm_profile *ac = NULL, *dc = NULL;
	char string[16], *cur = string, *ptr;

	/* safety precaution, for now */
	if (nouveau_perflvl_wr != 7777)
		return -EPERM;

	strncpy(string, profile, sizeof(string));
	string[sizeof(string) - 1] = 0;
	if ((ptr = strchr(string, '\n')))
		*ptr = '\0';

	ptr = strsep(&cur, ",");
	if (ptr)
		ac = profile_find(dev, ptr);

	ptr = strsep(&cur, ",");
	if (ptr)
		dc = profile_find(dev, ptr);
	else
		dc = ac;

	if (ac == NULL || dc == NULL)
		return -EINVAL;

	pm->profile_ac = ac;
	pm->profile_dc = dc;
	nouveau_pm_trigger(dev);
	return 0;
}