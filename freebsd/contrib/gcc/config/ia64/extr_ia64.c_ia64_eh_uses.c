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
struct TYPE_2__ {int reg_save_b0; int reg_save_pr; int reg_save_ar_pfs; int reg_save_ar_unat; int reg_save_ar_lc; } ;

/* Variables and functions */
 TYPE_1__ current_frame_info ; 
 int /*<<< orphan*/  reload_completed ; 

int
ia64_eh_uses (int regno)
{
  if (! reload_completed)
    return 0;

  if (current_frame_info.reg_save_b0
      && regno == current_frame_info.reg_save_b0)
    return 1;
  if (current_frame_info.reg_save_pr
      && regno == current_frame_info.reg_save_pr)
    return 1;
  if (current_frame_info.reg_save_ar_pfs
      && regno == current_frame_info.reg_save_ar_pfs)
    return 1;
  if (current_frame_info.reg_save_ar_unat
      && regno == current_frame_info.reg_save_ar_unat)
    return 1;
  if (current_frame_info.reg_save_ar_lc
      && regno == current_frame_info.reg_save_ar_lc)
    return 1;

  return 0;
}