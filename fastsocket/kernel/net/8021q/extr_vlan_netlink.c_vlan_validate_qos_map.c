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
 int /*<<< orphan*/  IFLA_VLAN_QOS_MAX ; 
 int nla_validate_nested (struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_map_policy ; 

__attribute__((used)) static inline int vlan_validate_qos_map(struct nlattr *attr)
{
	if (!attr)
		return 0;
	return nla_validate_nested(attr, IFLA_VLAN_QOS_MAX, vlan_map_policy);
}