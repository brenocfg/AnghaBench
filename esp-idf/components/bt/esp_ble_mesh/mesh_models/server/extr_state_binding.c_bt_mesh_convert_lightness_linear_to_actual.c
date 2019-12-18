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
typedef  scalar_t__ u16_t ;

/* Variables and functions */
 float UINT16_MAX ; 
 float bt_mesh_sqrt (float) ; 

u16_t bt_mesh_convert_lightness_linear_to_actual(u16_t linear)
{
    return (u16_t) (UINT16_MAX * bt_mesh_sqrt(((float) linear / UINT16_MAX)));
}