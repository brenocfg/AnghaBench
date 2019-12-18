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
struct gdbarch_info {scalar_t__ osabi; TYPE_1__* bfd_arch_info; } ;
struct gdbarch {int dummy; } ;
struct gdb_osabi_handler {scalar_t__ osabi; int /*<<< orphan*/  (* init_osabi ) (struct gdbarch_info,struct gdbarch*) ;int /*<<< orphan*/  arch_info; struct gdb_osabi_handler* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  printable_name; } ;

/* Variables and functions */
 scalar_t__ GDB_OSABI_UNKNOWN ; 
 scalar_t__ can_run_code_for (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct gdb_osabi_handler* gdb_osabi_handler_list ; 
 int /*<<< orphan*/  gdbarch_osabi_name (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct gdbarch_info,struct gdbarch*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
gdbarch_init_osabi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdb_osabi_handler *handler;

  if (info.osabi == GDB_OSABI_UNKNOWN)
    {
      /* Don't complain about an unknown OSABI.  Assume the user knows
         what they are doing.  */
      return;
    }

  for (handler = gdb_osabi_handler_list; handler != NULL;
       handler = handler->next)
    {
      if (handler->osabi != info.osabi)
	continue;

      /* If the architecture described by ARCH_INFO can run code for
         the architcture we registered the handler for, then the
         handler is applicable.  Note, though, that if the handler is
         for an architecture that is a superset of ARCH_INFO, we can't
         use that --- it would be perfectly correct for it to install
         gdbarch methods that refer to registers / instructions /
         other facilities ARCH_INFO doesn't have.

         NOTE: kettenis/20021027: There may be more than one machine
	 type that is compatible with the desired machine type.  Right
	 now we simply return the first match, which is fine for now.
	 However, we might want to do something smarter in the future.  */
      /* NOTE: cagney/2003-10-23: The code for "a can_run_code_for b"
         is implemented using BFD's compatible method (a->compatible
         (b) == a -- the lowest common denominator between a and b is
         a).  That method's definition of compatible may not be as you
         expect.  For instance the test "amd64 can run code for i386"
         (or more generally "64-bit ISA can run code for the 32-bit
         ISA").  BFD doesn't normally consider 32-bit and 64-bit
         "compatible" so it doesn't succeed.  */
      if (can_run_code_for (info.bfd_arch_info, handler->arch_info))
	{
	  (*handler->init_osabi) (info, gdbarch);
	  return;
	}
    }

  warning
    ("A handler for the OS ABI \"%s\" is not built into this configuration\n"
     "of GDB.  Attempting to continue with the default %s settings.\n",
     gdbarch_osabi_name (info.osabi),
     info.bfd_arch_info->printable_name);
}