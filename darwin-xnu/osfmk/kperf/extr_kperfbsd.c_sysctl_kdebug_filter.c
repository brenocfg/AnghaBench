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
typedef  scalar_t__ uint32_t ;
struct sysctl_req {scalar_t__ oldptr; scalar_t__ newptr; scalar_t__ newlen; } ;
struct kperf_kdebug_filter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t KPERF_KDEBUG_FILTER_SIZE (scalar_t__) ; 
 int SYSCTL_OUT (struct sysctl_req*,struct kperf_kdebug_filter*,size_t) ; 
 scalar_t__ USER_ADDR_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ kperf_kdebug_get_filter (struct kperf_kdebug_filter**) ; 
 int kperf_kdebug_set_filter (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
sysctl_kdebug_filter(struct sysctl_req *req)
{
	assert(req != NULL);

	if (req->oldptr != USER_ADDR_NULL) {
		struct kperf_kdebug_filter *filter = NULL;
		uint32_t n_debugids = kperf_kdebug_get_filter(&filter);
		size_t filter_size = KPERF_KDEBUG_FILTER_SIZE(n_debugids);

		if (n_debugids == 0) {
			return EINVAL;
		}

		return SYSCTL_OUT(req, filter, filter_size);
	} else if (req->newptr != USER_ADDR_NULL) {
		return kperf_kdebug_set_filter(req->newptr, (uint32_t)req->newlen);
	} else {
		return EINVAL;
	}
}