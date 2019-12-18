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
struct frame_unwind {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/ * alpha_extra_func_info_t ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct frame_unwind const alpha_mdebug_frame_unwind ; 
 scalar_t__ alpha_mdebug_in_prologue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_proc_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_pc_unwind (struct frame_info*) ; 

const struct frame_unwind *
alpha_mdebug_frame_sniffer (struct frame_info *next_frame)
{
  CORE_ADDR pc = frame_pc_unwind (next_frame);
  alpha_extra_func_info_t proc_desc;

  /* If this PC does not map to a PDR, then clearly this isn't an
     mdebug frame.  */
  proc_desc = find_proc_desc (pc);
  if (proc_desc == NULL)
    return NULL;

  /* If we're in the prologue, the PDR for this frame is not yet valid.
     Say no here and we'll fall back on the heuristic unwinder.  */
  if (alpha_mdebug_in_prologue (pc, proc_desc))
    return NULL;

  return &alpha_mdebug_frame_unwind;
}