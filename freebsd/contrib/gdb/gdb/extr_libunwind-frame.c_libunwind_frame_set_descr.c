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
struct libunwind_descr {int /*<<< orphan*/  accessors; int /*<<< orphan*/  is_fpreg; int /*<<< orphan*/  uw2gdb; int /*<<< orphan*/  gdb2uw; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 struct libunwind_descr* gdbarch_data (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libunwind_descr_handle ; 
 struct libunwind_descr* libunwind_descr_init (struct gdbarch*) ; 
 int /*<<< orphan*/  set_gdbarch_data (struct gdbarch*,int /*<<< orphan*/ ,struct libunwind_descr*) ; 

void
libunwind_frame_set_descr (struct gdbarch *gdbarch, struct libunwind_descr *descr)
{
  struct libunwind_descr *arch_descr;

  gdb_assert (gdbarch != NULL);

  arch_descr = gdbarch_data (gdbarch, libunwind_descr_handle);

  if (arch_descr == NULL)
    {
      /* First time here.  Must initialize data area.  */
      arch_descr = libunwind_descr_init (gdbarch);
      set_gdbarch_data (gdbarch, libunwind_descr_handle, arch_descr);
    }

  /* Copy new descriptor info into arch descriptor.  */
  arch_descr->gdb2uw = descr->gdb2uw;
  arch_descr->uw2gdb = descr->uw2gdb;
  arch_descr->is_fpreg = descr->is_fpreg;
  arch_descr->accessors = descr->accessors;
}