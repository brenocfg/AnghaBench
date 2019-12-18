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
typedef  int /*<<< orphan*/  tun_key ;
struct sw_flow_actions {int dummy; } ;
struct ovs_key_ipv4_tunnel {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVS_ACTION_ATTR_SET ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_IPV4_TUNNEL ; 
 int add_action (struct sw_flow_actions**,int /*<<< orphan*/ ,struct ovs_key_ipv4_tunnel*,int) ; 
 int /*<<< orphan*/  add_nested_action_end (struct sw_flow_actions*,int) ; 
 int add_nested_action_start (struct sw_flow_actions**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr const*) ; 
 int ovs_ipv4_tun_from_nlattr (int /*<<< orphan*/ ,struct ovs_key_ipv4_tunnel*) ; 

__attribute__((used)) static int validate_and_copy_set_tun(const struct nlattr *attr,
				     struct sw_flow_actions **sfa)
{
	struct ovs_key_ipv4_tunnel tun_key;
	int err, start;

	err = ovs_ipv4_tun_from_nlattr(nla_data(attr), &tun_key);
	if (err)
		return err;

	start = add_nested_action_start(sfa, OVS_ACTION_ATTR_SET);
	if (start < 0)
		return start;

	err = add_action(sfa, OVS_KEY_ATTR_IPV4_TUNNEL, &tun_key, sizeof(tun_key));
	add_nested_action_end(*sfa, start);

	return err;
}