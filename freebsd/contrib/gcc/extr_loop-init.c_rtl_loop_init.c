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
 int /*<<< orphan*/  LOOPS_NORMAL ; 
 int /*<<< orphan*/  cfg_layout_initialize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_loops ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_flags ; 
 int /*<<< orphan*/  dump_flow_info (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop_optimizer_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
rtl_loop_init (void)
{
  if (dump_file)
    dump_flow_info (dump_file, dump_flags);

  /* Initialize structures for layout changes.  */
  cfg_layout_initialize (0);

  current_loops = loop_optimizer_init (LOOPS_NORMAL);
  return 0;
}