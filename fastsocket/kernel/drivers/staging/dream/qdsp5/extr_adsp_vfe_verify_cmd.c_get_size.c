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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t get_size(uint32_t hw)
{
	uint32_t height, width;
	uint32_t height_mask = 0x3ffc;
	uint32_t width_mask = 0x3ffc000;

	height = (hw & height_mask) >> 2;
	width = (hw & width_mask) >> 14 ;
	return height * width;
}