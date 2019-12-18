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
typedef  float s16_t ;

/* Variables and functions */
 float INT16_MIN ; 
 float UINT16_MAX ; 

u16_t bt_mesh_covert_gen_level_to_temperature(s16_t level, u16_t min, u16_t max)
{
    float diff = (float) (max - min) / UINT16_MAX;
    u16_t tmp = (u16_t) ((level - INT16_MIN) * diff);
    return (u16_t) (min + tmp);
}