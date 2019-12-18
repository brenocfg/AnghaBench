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
struct msm_adsp_module {int /*<<< orphan*/  name; } ;
struct adsp_info {unsigned int module_count; } ;

/* Variables and functions */
 struct msm_adsp_module* adsp_modules ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct msm_adsp_module *find_adsp_module_by_name(
	struct adsp_info *info, const char *name)
{
	unsigned n;
	for (n = 0; n < info->module_count; n++)
		if (!strcmp(name, adsp_modules[n].name))
			return adsp_modules + n;
	return NULL;
}