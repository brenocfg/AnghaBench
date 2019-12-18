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
struct o2nm_cluster {unsigned int cl_keepalive_delay_ms; unsigned int cl_idle_timeout_ms; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ o2net_num_connected_peers () ; 
 int /*<<< orphan*/  o2nm_cluster_attr_write (char const*,size_t,unsigned int*) ; 

__attribute__((used)) static ssize_t o2nm_cluster_attr_keepalive_delay_ms_write(
	struct o2nm_cluster *cluster, const char *page, size_t count)
{
	ssize_t ret;
	unsigned int val;

	ret =  o2nm_cluster_attr_write(page, count, &val);

	if (ret > 0) {
		if (cluster->cl_keepalive_delay_ms != val
		    && o2net_num_connected_peers()) {
			mlog(ML_NOTICE,
			     "o2net: cannot change keepalive delay after"
			     " the first peer has agreed to it."
			     "  %d connected peers\n",
			     o2net_num_connected_peers());
			ret = -EINVAL;
		} else if (val >= cluster->cl_idle_timeout_ms) {
			mlog(ML_NOTICE, "o2net: keepalive delay must be "
			     "smaller than idle timeout\n");
			ret = -EINVAL;
		} else {
			cluster->cl_keepalive_delay_ms = val;
		}
	}

	return ret;
}