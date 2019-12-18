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
typedef  struct frame_info frame_info ;

/* Variables and functions */
 scalar_t__ DUMMY_FRAME ; 
 int /*<<< orphan*/  generic_pop_dummy_frame () ; 
 struct frame_info* get_current_frame () ; 
 scalar_t__ get_frame_type (struct frame_info*) ; 
 void stub1 (struct frame_info*) ; 

void
generic_pop_current_frame (void (*popper) (struct frame_info * frame))
{
  struct frame_info *frame = get_current_frame ();
  if (get_frame_type (frame) == DUMMY_FRAME)
    /* NOTE: cagney/2002-22-23: Does this ever occure?  Surely a dummy
       frame will have already been poped by the "infrun.c" code.  */
    generic_pop_dummy_frame ();
  else
    (*popper) (frame);
}