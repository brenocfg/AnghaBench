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
struct netsvctype_dscp_map {size_t netsvctype; int /*<<< orphan*/  dscp; } ;
struct net_qos_dscp_map {int /*<<< orphan*/ * netsvctype_to_dscp; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 size_t MIN (int /*<<< orphan*/ ,size_t) ; 
 size_t _MAX_DSCP ; 
 int /*<<< orphan*/  _NET_SERVICE_TYPE_COUNT ; 
 struct net_qos_dscp_map default_net_qos_dscp_map ; 

__attribute__((used)) static errno_t
get_netsvctype_dscp_map(size_t *out_count,
    struct netsvctype_dscp_map *netsvctype_dscp_map)
{
	size_t i;
	struct net_qos_dscp_map *net_qos_dscp_map = NULL;

	/*
	 * Do not accept more that max number of distinct DSCPs
	 */
	if (out_count == NULL || netsvctype_dscp_map == NULL)
		return (EINVAL);
	if (*out_count > _MAX_DSCP)
		return (EINVAL);

	net_qos_dscp_map = &default_net_qos_dscp_map;

	for (i = 0; i < MIN(_NET_SERVICE_TYPE_COUNT, *out_count); i++) {
		netsvctype_dscp_map[i].netsvctype = i;
		netsvctype_dscp_map[i].dscp = net_qos_dscp_map->netsvctype_to_dscp[i];

	}
	*out_count = i;

	return (0);
}