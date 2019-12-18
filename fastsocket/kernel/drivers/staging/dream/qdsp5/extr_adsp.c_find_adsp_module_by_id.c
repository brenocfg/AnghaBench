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
typedef  size_t uint32_t ;
struct msm_adsp_module {int dummy; } ;
struct adsp_info {size_t max_module_id; struct msm_adsp_module** id_to_module; } ;

/* Variables and functions */
 size_t get_module_index (size_t) ; 

__attribute__((used)) static struct msm_adsp_module *find_adsp_module_by_id(
	struct adsp_info *info, uint32_t id)
{
	if (id > info->max_module_id) {
		return NULL;
	} else {
#if CONFIG_MSM_AMSS_VERSION >= 6350
		id = get_module_index(id);
		if (id < 0)
			return NULL;
#endif
		return info->id_to_module[id];
	}
}