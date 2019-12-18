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
struct objfile {int dummy; } ;
struct minimal_symbol {int dummy; } ;
struct gdbarch {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 struct minimal_symbol* find_minsym_and_objfile (char*,struct objfile**) ; 
 scalar_t__ frame_pc_unwind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_current_frame () ; 
 struct minimal_symbol* lookup_minimal_symbol (char*,int /*<<< orphan*/ *,struct objfile*) ; 

CORE_ADDR
glibc_skip_solib_resolver (struct gdbarch *gdbarch, CORE_ADDR pc)
{
  /* The GNU dynamic linker is part of the GNU C library, and is used
     by all GNU systems (GNU/Hurd, GNU/Linux).  An unresolved PLT
     entry points to "_dl_runtime_resolve", which calls "fixup" to
     patch the PLT, and then passes control to the function.

     We look for the symbol `_dl_runtime_resolve', and find `fixup' in
     the same objfile.  If we are at the entry point of `fixup', then
     we set a breakpoint at the return address (at the top of the
     stack), and continue.
  
     It's kind of gross to do all these checks every time we're
     called, since they don't change once the executable has gotten
     started.  But this is only a temporary hack --- upcoming versions
     of GNU/Linux will provide a portable, efficient interface for
     debugging programs that use shared libraries.  */

  struct objfile *objfile;
  struct minimal_symbol *resolver 
    = find_minsym_and_objfile ("_dl_runtime_resolve", &objfile);

  if (resolver)
    {
      struct minimal_symbol *fixup
	= lookup_minimal_symbol ("fixup", NULL, objfile);

      if (fixup && SYMBOL_VALUE_ADDRESS (fixup) == pc)
	return frame_pc_unwind (get_current_frame ());
    }

  return 0;
}