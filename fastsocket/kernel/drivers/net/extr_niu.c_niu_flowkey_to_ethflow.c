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
typedef  int u64 ;

/* Variables and functions */
 int FLOW_KEY_IPDA ; 
 int FLOW_KEY_IPSA ; 
 int FLOW_KEY_L2DA ; 
 int FLOW_KEY_L4_0_SHIFT ; 
 int FLOW_KEY_L4_1_SHIFT ; 
 int FLOW_KEY_L4_BYTE12 ; 
 int FLOW_KEY_PROTO ; 
 int FLOW_KEY_VLAN ; 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L2DA ; 
 int RXH_L3_PROTO ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
 int RXH_VLAN ; 

__attribute__((used)) static u64 niu_flowkey_to_ethflow(u64 flow_key)
{
	u64 ethflow = 0;

	if (flow_key & FLOW_KEY_L2DA)
		ethflow |= RXH_L2DA;
	if (flow_key & FLOW_KEY_VLAN)
		ethflow |= RXH_VLAN;
	if (flow_key & FLOW_KEY_IPSA)
		ethflow |= RXH_IP_SRC;
	if (flow_key & FLOW_KEY_IPDA)
		ethflow |= RXH_IP_DST;
	if (flow_key & FLOW_KEY_PROTO)
		ethflow |= RXH_L3_PROTO;
	if (flow_key & (FLOW_KEY_L4_BYTE12 << FLOW_KEY_L4_0_SHIFT))
		ethflow |= RXH_L4_B_0_1;
	if (flow_key & (FLOW_KEY_L4_BYTE12 << FLOW_KEY_L4_1_SHIFT))
		ethflow |= RXH_L4_B_2_3;

	return ethflow;

}