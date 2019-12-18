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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ MLX4_VGT ; 

__attribute__((used)) static int calculate_transition(u16 oper_vlan, u16 admin_vlan)
{
	return (2 * (oper_vlan == MLX4_VGT) + (admin_vlan == MLX4_VGT));
}