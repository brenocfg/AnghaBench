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
struct frame_info {scalar_t__ type; TYPE_1__* unwind; int /*<<< orphan*/  next; } ;
typedef  enum frame_type { ____Placeholder_frame_type } frame_type ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_USE_GENERIC_DUMMY_FRAMES ; 
 int DUMMY_FRAME ; 
 int NORMAL_FRAME ; 
 scalar_t__ UNKNOWN_FRAME ; 
 int /*<<< orphan*/  current_gdbarch ; 
 scalar_t__ deprecated_frame_in_dummy (struct frame_info*) ; 
 TYPE_1__* frame_unwind_find_by_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  legacy_frame_p (int /*<<< orphan*/ ) ; 

enum frame_type
get_frame_type (struct frame_info *frame)
{
  /* Some targets still don't use [generic] dummy frames.  Catch them
     here.  */
  if (!DEPRECATED_USE_GENERIC_DUMMY_FRAMES
      && deprecated_frame_in_dummy (frame))
    return DUMMY_FRAME;

  /* Some legacy code, e.g, mips_init_extra_frame_info() wants
     to determine the frame's type prior to it being completely
     initialized.  Don't attempt to lazily initialize ->unwind for
     legacy code.  It will be initialized in legacy_get_prev_frame().  */
  if (frame->unwind == NULL && !legacy_frame_p (current_gdbarch))
    {
      /* Initialize the frame's unwinder because it is that which
         provides the frame's type.  */
      frame->unwind = frame_unwind_find_by_frame (frame->next);
      /* FIXME: cagney/2003-04-02: Rather than storing the frame's
	 type in the frame, the unwinder's type should be returned
	 directly.  Unfortunately, legacy code, called by
	 legacy_get_prev_frame, explicitly set the frames type using
	 the method deprecated_set_frame_type().  */
      frame->type = frame->unwind->type;
    }
  if (frame->type == UNKNOWN_FRAME)
    return NORMAL_FRAME;
  else
    return frame->type;
}