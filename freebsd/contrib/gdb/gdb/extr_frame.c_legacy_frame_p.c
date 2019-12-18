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
struct gdbarch {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEPRECATED_FP_REGNUM ; 
 scalar_t__ DEPRECATED_FRAME_CHAIN_P () ; 
 scalar_t__ DEPRECATED_INIT_EXTRA_FRAME_INFO_P () ; 
 scalar_t__ DEPRECATED_INIT_FRAME_PC_FIRST_P () ; 
 scalar_t__ DEPRECATED_INIT_FRAME_PC_P () ; 
 scalar_t__ DEPRECATED_TARGET_READ_FP_P () ; 
 scalar_t__ gdbarch_unwind_dummy_id_p (struct gdbarch*) ; 

int
legacy_frame_p (struct gdbarch *current_gdbarch)
{
  if (DEPRECATED_INIT_FRAME_PC_P ()
      || DEPRECATED_INIT_FRAME_PC_FIRST_P ()
      || DEPRECATED_INIT_EXTRA_FRAME_INFO_P ()
      || DEPRECATED_FRAME_CHAIN_P ())
    /* No question, it's a legacy frame.  */
    return 1;
  if (gdbarch_unwind_dummy_id_p (current_gdbarch))
    /* No question, it's not a legacy frame (provided none of the
       deprecated methods checked above are present that is).  */
    return 0;
  if (DEPRECATED_TARGET_READ_FP_P ()
      || DEPRECATED_FP_REGNUM >= 0)
    /* Assume it's legacy.  If you're trying to convert a legacy frame
       target to the new mechanism, get rid of these.  legacy
       get_prev_frame requires these when unwind_frame_id isn't
       available.  */
    return 1;
  /* Default to assuming that it's brand new code, and hence not
     legacy.  Force it down the non-legacy path so that the new code
     uses the new frame mechanism from day one.  Dummy frame's won't
     work very well but we can live with that.  */
  return 0;
}