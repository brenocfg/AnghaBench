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
struct gdbarch {struct frame_id (* unwind_dummy_id ) (struct gdbarch*,struct frame_info*) ;} ;
struct frame_info {int dummy; } ;
struct frame_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 struct frame_id stub1 (struct gdbarch*,struct frame_info*) ; 

struct frame_id
gdbarch_unwind_dummy_id (struct gdbarch *gdbarch, struct frame_info *info)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->unwind_dummy_id != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_unwind_dummy_id called\n");
  return gdbarch->unwind_dummy_id (gdbarch, info);
}