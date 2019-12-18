#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  gr_used_mask; } ;
struct TYPE_3__ {int /*<<< orphan*/  save_gr_used_mask; } ;

/* Variables and functions */
 TYPE_2__ current_frame_info ; 
 TYPE_1__ spill_fill_data ; 

__attribute__((used)) static void
finish_spill_pointers (void)
{
  current_frame_info.gr_used_mask = spill_fill_data.save_gr_used_mask;
}