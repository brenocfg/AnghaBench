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
struct frame_info {int dummy; } ;
typedef  scalar_t__ bfd_vma ;

/* Variables and functions */
 scalar_t__ INNER_THAN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gdb_assert (scalar_t__*) ; 
 struct frame_info* get_current_frame () ; 
 scalar_t__ get_frame_base (struct frame_info*) ; 
 struct frame_info* get_prev_frame (struct frame_info*) ; 
 scalar_t__ read_sp () ; 
 int /*<<< orphan*/  target_has_registers ; 
 int /*<<< orphan*/  target_has_stack ; 

__attribute__((used)) static int
derive_stack_segment (bfd_vma *bottom, bfd_vma *top)
{
  struct frame_info *fi, *tmp_fi;

  gdb_assert (bottom);
  gdb_assert (top);

  /* Can't succeed without stack and registers.  */
  if (!target_has_stack || !target_has_registers)
    return 0;

  /* Can't succeed without current frame.  */
  fi = get_current_frame ();
  if (fi == NULL)
    return 0;

  /* Save frame pointer of TOS frame.  */
  *top = get_frame_base (fi);
  /* If current stack pointer is more "inner", use that instead.  */
  if (INNER_THAN (read_sp (), *top))
    *top = read_sp ();

  /* Find prev-most frame.  */
  while ((tmp_fi = get_prev_frame (fi)) != NULL)
    fi = tmp_fi;

  /* Save frame pointer of prev-most frame.  */
  *bottom = get_frame_base (fi);

  /* Now canonicalize their order, so that BOTTOM is a lower address
     (as opposed to a lower stack frame).  */
  if (*bottom > *top)
    {
      bfd_vma tmp_vma;

      tmp_vma = *top;
      *top = *bottom;
      *bottom = tmp_vma;
    }

  return 1;
}