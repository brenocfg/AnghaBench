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

/* Variables and functions */
 int /*<<< orphan*/  CLEANUP_EXPENSIVE ; 
 int /*<<< orphan*/  TV_JUMP ; 
 int /*<<< orphan*/  cleanup_cfg (int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_flags ; 
 int /*<<< orphan*/  dump_flow_info (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_if_conversion ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  if_convert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_reg_num () ; 
 int /*<<< orphan*/  reg_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
rest_of_handle_if_conversion (void)
{
  if (flag_if_conversion)
    {
      if (dump_file)
        dump_flow_info (dump_file, dump_flags);
      cleanup_cfg (CLEANUP_EXPENSIVE);
      reg_scan (get_insns (), max_reg_num ());
      if_convert (0);
    }

  timevar_push (TV_JUMP);
  cleanup_cfg (CLEANUP_EXPENSIVE);
  reg_scan (get_insns (), max_reg_num ());
  timevar_pop (TV_JUMP);
  return 0;
}