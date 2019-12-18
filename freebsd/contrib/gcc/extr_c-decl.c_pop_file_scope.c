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

/* Variables and functions */
 int /*<<< orphan*/  c_common_write_pch () ; 
 int /*<<< orphan*/  cgraph_finalize_compilation_unit () ; 
 scalar_t__ current_scope ; 
 scalar_t__ file_scope ; 
 int /*<<< orphan*/  finish_fname_decls () ; 
 int /*<<< orphan*/  maybe_apply_pending_pragma_weaks () ; 
 scalar_t__ pch_file ; 
 int /*<<< orphan*/  pop_scope () ; 

void
pop_file_scope (void)
{
  /* In case there were missing closebraces, get us back to the global
     binding level.  */
  while (current_scope != file_scope)
    pop_scope ();

  /* __FUNCTION__ is defined at file scope ("").  This
     call may not be necessary as my tests indicate it
     still works without it.  */
  finish_fname_decls ();

  /* This is the point to write out a PCH if we're doing that.
     In that case we do not want to do anything else.  */
  if (pch_file)
    {
      c_common_write_pch ();
      return;
    }

  /* Pop off the file scope and close this translation unit.  */
  pop_scope ();
  file_scope = 0;

  maybe_apply_pending_pragma_weaks ();
  cgraph_finalize_compilation_unit ();
}