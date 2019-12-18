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
struct netsvctype_dscp_map {int netsvctype; size_t dscp; } ;
struct net_qos_dscp_map {size_t* netsvctype_to_dscp; size_t* sotc_to_dscp; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IS_VALID_NET_SERVICE_TYPE (int) ; 
#define  NET_SERVICE_TYPE_AV 136 
#define  NET_SERVICE_TYPE_BE 135 
#define  NET_SERVICE_TYPE_BK 134 
#define  NET_SERVICE_TYPE_OAM 133 
#define  NET_SERVICE_TYPE_RD 132 
#define  NET_SERVICE_TYPE_RV 131 
#define  NET_SERVICE_TYPE_SIG 130 
#define  NET_SERVICE_TYPE_VI 129 
#define  NET_SERVICE_TYPE_VO 128 
 size_t SIZE_T_MAX ; 
 size_t SOTCIX_BK ; 
 size_t SOTCIX_BK_SYS ; 
 size_t SOTCIX_CTL ; 
 size_t _DSCP_DF ; 
 size_t _MAX_DSCP ; 
 int _NET_SERVICE_TYPE_COUNT ; 
 struct net_qos_dscp_map default_net_qos_dscp_map ; 
 int /*<<< orphan*/ * sotc_by_netservicetype ; 
 size_t sotc_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
set_netsvctype_dscp_map(size_t in_count,
    const struct netsvctype_dscp_map *netsvctype_dscp_map)
{
	size_t i;
	struct net_qos_dscp_map *net_qos_dscp_map = NULL;
	int netsvctype;

	/*
	 * Do not accept more that max number of distinct DSCPs
	 */
	if (in_count > _MAX_DSCP || netsvctype_dscp_map == NULL)
		return (EINVAL);

	/*
	 * Validate input parameters
	 */
	for (i = 0; i < in_count; i++) {
		if (!IS_VALID_NET_SERVICE_TYPE(netsvctype_dscp_map[i].netsvctype))
			return (EINVAL);
		if (netsvctype_dscp_map[i].dscp > _MAX_DSCP)
			return (EINVAL);
	}

	net_qos_dscp_map = &default_net_qos_dscp_map;

	for (i = 0; i < in_count; i++) {
		netsvctype = netsvctype_dscp_map[i].netsvctype;

		net_qos_dscp_map->netsvctype_to_dscp[netsvctype] =
		    netsvctype_dscp_map[i].dscp;
	}
	for (netsvctype = 0; netsvctype < _NET_SERVICE_TYPE_COUNT; netsvctype++) {
		switch (netsvctype) {
			case NET_SERVICE_TYPE_BE:
			case NET_SERVICE_TYPE_BK:
			case NET_SERVICE_TYPE_VI:
			case NET_SERVICE_TYPE_VO:
			case NET_SERVICE_TYPE_RV:
			case NET_SERVICE_TYPE_AV:
			case NET_SERVICE_TYPE_OAM:
			case NET_SERVICE_TYPE_RD: {
				size_t sotcix;

				sotcix = sotc_index(sotc_by_netservicetype[netsvctype]);
				if (sotcix != SIZE_T_MAX) {
					net_qos_dscp_map->sotc_to_dscp[sotcix]  =
					    netsvctype_dscp_map[netsvctype].dscp;
				}
				break;
			}
			case  NET_SERVICE_TYPE_SIG:
				/* Signaling does not have its own traffic class */
				break;
			default:
				/* We should not be here */
				ASSERT(0);
		}
	}
	/* Network control socket traffic class is always best effort */
	net_qos_dscp_map->sotc_to_dscp[SOTCIX_CTL] = _DSCP_DF;

	/* Backround socket traffic class DSCP same as backround system */
	net_qos_dscp_map->sotc_to_dscp[SOTCIX_BK] =
	   net_qos_dscp_map->sotc_to_dscp[SOTCIX_BK_SYS];

	return (0);
}