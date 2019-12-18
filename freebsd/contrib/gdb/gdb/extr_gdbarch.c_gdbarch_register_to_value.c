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
struct type {int dummy; } ;
struct gdbarch {int /*<<< orphan*/  (* register_to_value ) (struct frame_info*,int,struct type*,void*) ;} ;
struct frame_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int /*<<< orphan*/  stub1 (struct frame_info*,int,struct type*,void*) ; 

void
gdbarch_register_to_value (struct gdbarch *gdbarch, struct frame_info *frame, int regnum, struct type *type, void *buf)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->register_to_value != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_register_to_value called\n");
  gdbarch->register_to_value (frame, regnum, type, buf);
}