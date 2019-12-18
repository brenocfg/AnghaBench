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
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t IPVS_DAEMON_ATTR_MCAST_IFN ; 
 size_t IPVS_DAEMON_ATTR_STATE ; 
 size_t IPVS_DAEMON_ATTR_SYNC_ID ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int start_sync_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip_vs_genl_new_daemon(struct nlattr **attrs)
{
	if (!(attrs[IPVS_DAEMON_ATTR_STATE] &&
	      attrs[IPVS_DAEMON_ATTR_MCAST_IFN] &&
	      attrs[IPVS_DAEMON_ATTR_SYNC_ID]))
		return -EINVAL;

	return start_sync_thread(nla_get_u32(attrs[IPVS_DAEMON_ATTR_STATE]),
				 nla_data(attrs[IPVS_DAEMON_ATTR_MCAST_IFN]),
				 nla_get_u32(attrs[IPVS_DAEMON_ATTR_SYNC_ID]));
}