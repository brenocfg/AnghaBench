#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ total_size; scalar_t__ n_spilled; scalar_t__ reg_save_b0; scalar_t__ reg_save_pr; scalar_t__ reg_save_ar_pfs; scalar_t__ reg_save_ar_unat; scalar_t__ reg_save_ar_lc; } ;

/* Variables and functions */
 TYPE_1__ current_frame_info ; 
 int /*<<< orphan*/  frame_pointer_needed ; 
 int /*<<< orphan*/  get_frame_size () ; 
 int /*<<< orphan*/  ia64_compute_frame_size (int /*<<< orphan*/ ) ; 
 scalar_t__ reload_completed ; 

int
ia64_direct_return (void)
{
  if (reload_completed && ! frame_pointer_needed)
    {
      ia64_compute_frame_size (get_frame_size ());

      return (current_frame_info.total_size == 0
	      && current_frame_info.n_spilled == 0
	      && current_frame_info.reg_save_b0 == 0
	      && current_frame_info.reg_save_pr == 0
	      && current_frame_info.reg_save_ar_pfs == 0
	      && current_frame_info.reg_save_ar_unat == 0
	      && current_frame_info.reg_save_ar_lc == 0);
    }
  return 0;
}