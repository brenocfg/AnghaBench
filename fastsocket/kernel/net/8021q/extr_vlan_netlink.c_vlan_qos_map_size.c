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
struct ifla_vlan_qos_mapping {int dummy; } ;

/* Variables and functions */
 unsigned int nla_total_size (int) ; 

__attribute__((used)) static inline size_t vlan_qos_map_size(unsigned int n)
{
	if (n == 0)
		return 0;
	/* IFLA_VLAN_{EGRESS,INGRESS}_QOS + n * IFLA_VLAN_QOS_MAPPING */
	return nla_total_size(sizeof(struct nlattr)) +
	       nla_total_size(sizeof(struct ifla_vlan_qos_mapping)) * n;
}