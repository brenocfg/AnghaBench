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
typedef  scalar_t__ u32 ;
struct dum_ch_setup {scalar_t__ ymin; scalar_t__ ymax; } ;

/* Variables and functions */

__attribute__((used)) static u32 nof_pixels_dy(struct dum_ch_setup *ch_setup)
{
	return (ch_setup->ymax - ch_setup->ymin + 1);
}