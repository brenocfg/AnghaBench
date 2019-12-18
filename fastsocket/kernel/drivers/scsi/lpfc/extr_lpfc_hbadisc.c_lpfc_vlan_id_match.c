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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */

__attribute__((used)) static bool
lpfc_vlan_id_match(uint16_t curr_vlan_id, uint16_t new_vlan_id)
{
	return (curr_vlan_id == new_vlan_id);
}