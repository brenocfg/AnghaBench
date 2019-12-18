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
struct gdbarch {int dummy; } ;
struct frame_unwind_table {int dummy; } ;
typedef  int /*<<< orphan*/  frame_unwind_sniffer_ftype ;

/* Variables and functions */
 int /*<<< orphan*/  append_predicate (struct frame_unwind_table*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_unwind_data ; 
 struct frame_unwind_table* frame_unwind_init (struct gdbarch*) ; 
 struct frame_unwind_table* gdbarch_data (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_data (struct gdbarch*,int /*<<< orphan*/ ,struct frame_unwind_table*) ; 

void
frame_unwind_append_sniffer (struct gdbarch *gdbarch,
			     frame_unwind_sniffer_ftype *sniffer)
{
  struct frame_unwind_table *table =
    gdbarch_data (gdbarch, frame_unwind_data);
  if (table == NULL)
    {
      /* ULGH, called during architecture initialization.  Patch
         things up.  */
      table = frame_unwind_init (gdbarch);
      set_gdbarch_data (gdbarch, frame_unwind_data, table);
    }
  append_predicate (table, sniffer);
}