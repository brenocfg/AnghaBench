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
typedef  union bnx2x_classification_ramrod_data {int dummy; } bnx2x_classification_ramrod_data ;
struct bnx2x_vlan_mac_obj {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool bnx2x_check_move_always_err(
	struct bnx2x *bp,
	struct bnx2x_vlan_mac_obj *src_o,
	struct bnx2x_vlan_mac_obj *dst_o,
	union bnx2x_classification_ramrod_data *data)
{
	return false;
}