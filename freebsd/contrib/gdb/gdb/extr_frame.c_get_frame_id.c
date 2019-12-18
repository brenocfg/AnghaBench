#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct frame_id {int dummy; } ;
struct TYPE_3__ {int p; struct frame_id value; } ;
struct frame_info {TYPE_1__ this_id; int /*<<< orphan*/  prologue_cache; int /*<<< orphan*/  next; TYPE_2__* unwind; int /*<<< orphan*/  type; int /*<<< orphan*/  level; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* this_id ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct frame_id*) ;int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  fprint_frame_id (int /*<<< orphan*/ ,struct frame_id) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ frame_debug ; 
 TYPE_2__* frame_unwind_find_by_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  legacy_frame_p (int /*<<< orphan*/ ) ; 
 struct frame_id null_frame_id ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct frame_id*) ; 

struct frame_id
get_frame_id (struct frame_info *fi)
{
  if (fi == NULL)
    {
      return null_frame_id;
    }
  if (!fi->this_id.p)
    {
      gdb_assert (!legacy_frame_p (current_gdbarch));
      if (frame_debug)
	fprintf_unfiltered (gdb_stdlog, "{ get_frame_id (fi=%d) ",
			    fi->level);
      /* Find the unwinder.  */
      if (fi->unwind == NULL)
	{
	  fi->unwind = frame_unwind_find_by_frame (fi->next);
	  /* FIXME: cagney/2003-04-02: Rather than storing the frame's
	     type in the frame, the unwinder's type should be returned
	     directly.  Unfortunately, legacy code, called by
	     legacy_get_prev_frame, explicitly set the frames type
	     using the method deprecated_set_frame_type().  */
	  fi->type = fi->unwind->type;
	}
      /* Find THIS frame's ID.  */
      fi->unwind->this_id (fi->next, &fi->prologue_cache, &fi->this_id.value);
      fi->this_id.p = 1;
      if (frame_debug)
	{
	  fprintf_unfiltered (gdb_stdlog, "-> ");
	  fprint_frame_id (gdb_stdlog, fi->this_id.value);
	  fprintf_unfiltered (gdb_stdlog, " }\n");
	}
    }
  return fi->this_id.value;
}