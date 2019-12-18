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
struct frame_unwind_cache {int dummy; } ;
struct frame_info {int /*<<< orphan*/  prologue_cache; int /*<<< orphan*/  next; TYPE_1__* unwind; int /*<<< orphan*/  type; int /*<<< orphan*/  level; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
struct TYPE_2__ {int /*<<< orphan*/  (* prev_register ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int*,int /*<<< orphan*/ *,int*,void*) ;int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ frame_debug ; 
 int /*<<< orphan*/  frame_map_regnum_to_name (struct frame_info*,int) ; 
 TYPE_1__* frame_unwind_find_by_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  paddr_nz (int /*<<< orphan*/ ) ; 
 int register_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int*,int /*<<< orphan*/ *,int*,void*) ; 

void
frame_register_unwind (struct frame_info *frame, int regnum,
		       int *optimizedp, enum lval_type *lvalp,
		       CORE_ADDR *addrp, int *realnump, void *bufferp)
{
  struct frame_unwind_cache *cache;

  if (frame_debug)
    {
      fprintf_unfiltered (gdb_stdlog, "\
{ frame_register_unwind (frame=%d,regnum=%d(%s),...) ",
			  frame->level, regnum,
			  frame_map_regnum_to_name (frame, regnum));
    }

  /* Require all but BUFFERP to be valid.  A NULL BUFFERP indicates
     that the value proper does not need to be fetched.  */
  gdb_assert (optimizedp != NULL);
  gdb_assert (lvalp != NULL);
  gdb_assert (addrp != NULL);
  gdb_assert (realnump != NULL);
  /* gdb_assert (bufferp != NULL); */

  /* NOTE: cagney/2002-11-27: A program trying to unwind a NULL frame
     is broken.  There is always a frame.  If there, for some reason,
     isn't, there is some pretty busted code as it should have
     detected the problem before calling here.  */
  gdb_assert (frame != NULL);

  /* Find the unwinder.  */
  if (frame->unwind == NULL)
    {
      frame->unwind = frame_unwind_find_by_frame (frame->next);
      /* FIXME: cagney/2003-04-02: Rather than storing the frame's
	 type in the frame, the unwinder's type should be returned
	 directly.  Unfortunately, legacy code, called by
	 legacy_get_prev_frame, explicitly set the frames type using
	 the method deprecated_set_frame_type().  */
      frame->type = frame->unwind->type;
    }

  /* Ask this frame to unwind its register.  See comment in
     "frame-unwind.h" for why NEXT frame and this unwind cace are
     passed in.  */
  frame->unwind->prev_register (frame->next, &frame->prologue_cache, regnum,
				optimizedp, lvalp, addrp, realnump, bufferp);

  if (frame_debug)
    {
      fprintf_unfiltered (gdb_stdlog, "->");
      fprintf_unfiltered (gdb_stdlog, " *optimizedp=%d", (*optimizedp));
      fprintf_unfiltered (gdb_stdlog, " *lvalp=%d", (int) (*lvalp));
      fprintf_unfiltered (gdb_stdlog, " *addrp=0x%s", paddr_nz ((*addrp)));
      fprintf_unfiltered (gdb_stdlog, " *bufferp=");
      if (bufferp == NULL)
	fprintf_unfiltered (gdb_stdlog, "<NULL>");
      else
	{
	  int i;
	  const unsigned char *buf = bufferp;
	  fprintf_unfiltered (gdb_stdlog, "[");
	  for (i = 0; i < register_size (current_gdbarch, regnum); i++)
	    fprintf_unfiltered (gdb_stdlog, "%02x", buf[i]);
	  fprintf_unfiltered (gdb_stdlog, "]");
	}
      fprintf_unfiltered (gdb_stdlog, " }\n");
    }
}