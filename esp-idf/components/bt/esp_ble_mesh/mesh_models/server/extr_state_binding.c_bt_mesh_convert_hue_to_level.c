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
typedef  int /*<<< orphan*/  s16_t ;

/* Variables and functions */
 scalar_t__ INT16_MIN ; 

s16_t bt_mesh_convert_hue_to_level(u16_t hue)
{
    return (s16_t) (hue + INT16_MIN);
}