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
struct sn_hwperf_object_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ SN_HWPERF_IS_IONODE (struct sn_hwperf_object_info*) ; 
 int SN_HWPERF_IS_NODE (struct sn_hwperf_object_info*) ; 
 scalar_t__ SN_HWPERF_IS_ROUTER (struct sn_hwperf_object_info*) ; 
 char* slabname_ionode ; 
 char* slabname_node ; 
 char* slabname_other ; 
 char* slabname_router ; 
 int sn_hwperf_generic_ordinal (struct sn_hwperf_object_info*,struct sn_hwperf_object_info*) ; 
 int sn_hwperf_obj_to_cnode (struct sn_hwperf_object_info*) ; 

__attribute__((used)) static const char *sn_hwperf_get_slabname(struct sn_hwperf_object_info *obj,
			struct sn_hwperf_object_info *objs, int *ordinal)
{
	int isnode;
	const char *slabname = slabname_other;

	if ((isnode = SN_HWPERF_IS_NODE(obj)) || SN_HWPERF_IS_IONODE(obj)) {
	    	slabname = isnode ? slabname_node : slabname_ionode;
		*ordinal = sn_hwperf_obj_to_cnode(obj);
	}
	else {
		*ordinal = sn_hwperf_generic_ordinal(obj, objs);
		if (SN_HWPERF_IS_ROUTER(obj))
			slabname = slabname_router;
	}

	return slabname;
}