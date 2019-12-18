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
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  printable_name; } ;

/* Variables and functions */
 struct gdbarch* current_gdbarch ; 
 int /*<<< orphan*/  deprecated_current_gdbarch_select_hack (struct gdbarch*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 TYPE_1__* gdbarch_bfd_arch_info (struct gdbarch*) ; 
 scalar_t__ gdbarch_debug ; 
 struct gdbarch* gdbarch_find_by_info (struct gdbarch_info) ; 

int
gdbarch_update_p (struct gdbarch_info info)
{
  struct gdbarch *new_gdbarch = gdbarch_find_by_info (info);

  /* If there no architecture by that name, reject the request.  */
  if (new_gdbarch == NULL)
    {
      if (gdbarch_debug)
	fprintf_unfiltered (gdb_stdlog, "gdbarch_update_p: "
			    "Architecture not found\n");
      return 0;
    }

  /* If it is the same old architecture, accept the request (but don't
     swap anything).  */
  if (new_gdbarch == current_gdbarch)
    {
      if (gdbarch_debug)
	fprintf_unfiltered (gdb_stdlog, "gdbarch_update_p: "
			    "Architecture 0x%08lx (%s) unchanged\n",
			    (long) new_gdbarch,
			    gdbarch_bfd_arch_info (new_gdbarch)->printable_name);
      return 1;
    }

  /* It's a new architecture, swap it in.  */
  if (gdbarch_debug)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_update_p: "
			"New architecture 0x%08lx (%s) selected\n",
			(long) new_gdbarch,
			gdbarch_bfd_arch_info (new_gdbarch)->printable_name);
  deprecated_current_gdbarch_select_hack (new_gdbarch);

  return 1;
}