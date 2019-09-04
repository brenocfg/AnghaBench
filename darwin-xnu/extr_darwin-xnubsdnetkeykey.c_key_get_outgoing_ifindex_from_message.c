#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct sadb_x_ipsecif {scalar_t__* sadb_x_ipsecif_outgoing_if; } ;
struct sadb_msghdr {scalar_t__* ext; } ;
typedef  TYPE_1__* ifnet_t ;
struct TYPE_3__ {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ifnet_find_by_name (scalar_t__*,TYPE_1__**) ; 

__attribute__((used)) static u_int
key_get_outgoing_ifindex_from_message (const struct sadb_msghdr *mhp, int message_type)
{
	struct sadb_x_ipsecif *ipsecifopts = NULL;
	ifnet_t outgoing_if = NULL;
	
	ipsecifopts = (struct sadb_x_ipsecif *)(void *)mhp->ext[message_type];
	if (ipsecifopts != NULL) {
		if (ipsecifopts->sadb_x_ipsecif_outgoing_if[0]) {
			ifnet_find_by_name(ipsecifopts->sadb_x_ipsecif_outgoing_if, &outgoing_if);
        }
    }
	
	return outgoing_if ? outgoing_if->if_index : 0;
}