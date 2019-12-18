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
struct TYPE_3__ {int p; } ;
struct frame_info {scalar_t__ type; TYPE_1__ this_id; TYPE_2__* unwind; int /*<<< orphan*/  next; } ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_INIT_EXTRA_FRAME_INFO (int /*<<< orphan*/ ,struct frame_info*) ; 
 scalar_t__ DEPRECATED_INIT_EXTRA_FRAME_INFO_P () ; 
 scalar_t__ UNKNOWN_FRAME ; 
 int /*<<< orphan*/  create_sentinel_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  deprecated_update_frame_base_hack (struct frame_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deprecated_update_frame_pc_hack (struct frame_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprint_frame (int /*<<< orphan*/ ,struct frame_info*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ frame_debug ; 
 struct frame_info* frame_obstack_zalloc (int) ; 
 scalar_t__ frame_type_from_pc (int /*<<< orphan*/ ) ; 
 TYPE_2__* frame_unwind_find_by_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  paddr_nz (int /*<<< orphan*/ ) ; 

struct frame_info *
create_new_frame (CORE_ADDR addr, CORE_ADDR pc)
{
  struct frame_info *fi;

  if (frame_debug)
    {
      fprintf_unfiltered (gdb_stdlog,
			  "{ create_new_frame (addr=0x%s, pc=0x%s) ",
			  paddr_nz (addr), paddr_nz (pc));
    }

  fi = frame_obstack_zalloc (sizeof (struct frame_info));

  fi->next = create_sentinel_frame (current_regcache);

  /* Select/initialize both the unwind function and the frame's type
     based on the PC.  */
  fi->unwind = frame_unwind_find_by_frame (fi->next);
  if (fi->unwind->type != UNKNOWN_FRAME)
    fi->type = fi->unwind->type;
  else
    fi->type = frame_type_from_pc (pc);

  fi->this_id.p = 1;
  deprecated_update_frame_base_hack (fi, addr);
  deprecated_update_frame_pc_hack (fi, pc);

  if (DEPRECATED_INIT_EXTRA_FRAME_INFO_P ())
    DEPRECATED_INIT_EXTRA_FRAME_INFO (0, fi);

  if (frame_debug)
    {
      fprintf_unfiltered (gdb_stdlog, "-> ");
      fprint_frame (gdb_stdlog, fi);
      fprintf_unfiltered (gdb_stdlog, " }\n");
    }

  return fi;
}