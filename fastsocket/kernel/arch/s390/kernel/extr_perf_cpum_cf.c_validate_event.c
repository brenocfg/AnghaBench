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
struct hw_perf_event {int config_base; int config; } ;

/* Variables and functions */
#define  CPUMF_CTR_SET_BASIC 131 
#define  CPUMF_CTR_SET_CRYPTO 130 
#define  CPUMF_CTR_SET_EXT 129 
#define  CPUMF_CTR_SET_USER 128 
 int EINVAL ; 
 int EOPNOTSUPP ; 

__attribute__((used)) static int validate_event(const struct hw_perf_event *hwc)
{
	switch (hwc->config_base) {
	case CPUMF_CTR_SET_BASIC:
	case CPUMF_CTR_SET_USER:
	case CPUMF_CTR_SET_CRYPTO:
	case CPUMF_CTR_SET_EXT:
		/* check for reserved counters */
		if ((hwc->config >=  6 && hwc->config <=  31) ||
		    (hwc->config >= 38 && hwc->config <=  63) ||
		    (hwc->config >= 80 && hwc->config <= 127))
			return -EOPNOTSUPP;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}