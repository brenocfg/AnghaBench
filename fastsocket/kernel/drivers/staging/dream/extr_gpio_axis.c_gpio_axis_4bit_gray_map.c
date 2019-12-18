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
typedef  size_t uint16_t ;
struct gpio_event_axis_info {int dummy; } ;

/* Variables and functions */
 size_t* gpio_axis_4bit_gray_map_table ; 

uint16_t gpio_axis_4bit_gray_map(struct gpio_event_axis_info *info, uint16_t in)
{
	return gpio_axis_4bit_gray_map_table[in];
}