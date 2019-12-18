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
 int /*<<< orphan*/  cleanup_cfg (int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_flags ; 
 int /*<<< orphan*/  dump_flow_info (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  max_reg_num () ; 
 int /*<<< orphan*/  reg_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
rest_of_handle_tracer (void)
{
  if (dump_file)
    dump_flow_info (dump_file, dump_flags);
  tracer (0);
  cleanup_cfg (CLEANUP_EXPENSIVE);
  reg_scan (get_insns (), max_reg_num ());
  return 0;
}