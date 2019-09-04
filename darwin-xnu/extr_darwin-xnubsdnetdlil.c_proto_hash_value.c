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
typedef  int u_int32_t ;

/* Variables and functions */
#define  PF_INET 131 
#define  PF_INET6 130 
#define  PF_UNSPEC 129 
#define  PF_VLAN 128 

int
proto_hash_value(u_int32_t protocol_family)
{
	/*
	 * dlil_proto_unplumb_all() depends on the mapping between
	 * the hash bucket index and the protocol family defined
	 * here; future changes must be applied there as well.
	 */
	switch (protocol_family) {
		case PF_INET:
			return (0);
		case PF_INET6:
			return (1);
		case PF_VLAN:
			return (2);
		case PF_UNSPEC:
		default:
			return (3);
	}
}