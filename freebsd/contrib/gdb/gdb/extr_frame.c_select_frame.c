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
struct symtab {scalar_t__ language; } ;
struct frame_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ la_language; } ;

/* Variables and functions */
 TYPE_1__* current_language ; 
 struct frame_info* deprecated_selected_frame ; 
 struct symtab* find_pc_symtab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_relative_level (struct frame_info*) ; 
 int /*<<< orphan*/  get_frame_address_in_block (struct frame_info*) ; 
 scalar_t__ language_mode ; 
 scalar_t__ language_mode_auto ; 
 scalar_t__ language_unknown ; 
 int /*<<< orphan*/  selected_frame_level_changed_hook (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_language (scalar_t__) ; 

void
select_frame (struct frame_info *fi)
{
  struct symtab *s;

  deprecated_selected_frame = fi;
  /* NOTE: cagney/2002-05-04: FI can be NULL.  This occures when the
     frame is being invalidated.  */
  if (selected_frame_level_changed_hook)
    selected_frame_level_changed_hook (frame_relative_level (fi));

  /* FIXME: kseitz/2002-08-28: It would be nice to call
     selected_frame_level_changed_event right here, but due to limitations
     in the current interfaces, we would end up flooding UIs with events
     because select_frame is used extensively internally.

     Once we have frame-parameterized frame (and frame-related) commands,
     the event notification can be moved here, since this function will only
     be called when the users selected frame is being changed. */

  /* Ensure that symbols for this frame are read in.  Also, determine the
     source language of this frame, and switch to it if desired.  */
  if (fi)
    {
      /* We retrieve the frame's symtab by using the frame PC.  However
         we cannot use the frame pc as is, because it usually points to
         the instruction following the "call", which is sometimes the
         first instruction of another function.  So we rely on
         get_frame_address_in_block() which provides us with a PC which
         is guaranteed to be inside the frame's code block.  */
      s = find_pc_symtab (get_frame_address_in_block (fi));
      if (s
	  && s->language != current_language->la_language
	  && s->language != language_unknown
	  && language_mode == language_mode_auto)
	{
	  set_language (s->language);
	}
    }
}