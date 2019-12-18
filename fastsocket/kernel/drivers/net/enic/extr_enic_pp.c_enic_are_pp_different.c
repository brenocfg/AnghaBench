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
struct enic_port_profile {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  host_uuid; int /*<<< orphan*/  instance_uuid; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  PORT_UUID_MAX ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enic_are_pp_different(struct enic_port_profile *pp1,
		struct enic_port_profile *pp2)
{
	return strcmp(pp1->name, pp2->name) | !!memcmp(pp1->instance_uuid,
		pp2->instance_uuid, PORT_UUID_MAX) |
		!!memcmp(pp1->host_uuid, pp2->host_uuid, PORT_UUID_MAX) |
		!!memcmp(pp1->mac_addr, pp2->mac_addr, ETH_ALEN);
}