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
typedef  float u16_t ;
typedef  int /*<<< orphan*/  s16_t ;

/* Variables and functions */
 scalar_t__ INT16_MIN ; 
 float UINT16_MAX ; 

s16_t bt_mesh_convert_temperature_to_gen_level(u16_t temp, u16_t min, u16_t max)
{
    float tmp = (temp - min) * UINT16_MAX / (max - min);
    return (s16_t) (tmp + INT16_MIN);
}