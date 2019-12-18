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
 scalar_t__ bt_mesh_ceiling (float) ; 

u16_t bt_mesh_convert_lightness_actual_to_linear(u16_t actual)
{
    float tmp = ((float) actual / UINT16_MAX);

    return bt_mesh_ceiling(UINT16_MAX * tmp * tmp);
}