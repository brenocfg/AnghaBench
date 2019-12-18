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
struct frame_base_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  frame_base_data ; 
 struct frame_base_table* frame_base_init (struct gdbarch*) ; 
 struct frame_base_table* gdbarch_data (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_data (struct gdbarch*,int /*<<< orphan*/ ,struct frame_base_table*) ; 

__attribute__((used)) static struct frame_base_table *
frame_base_table (struct gdbarch *gdbarch)
{
  struct frame_base_table *table = gdbarch_data (gdbarch, frame_base_data);
  if (table == NULL)
    {
      /* ULGH, called during architecture initialization.  Patch
         things up.  */
      table = frame_base_init (gdbarch);
      set_gdbarch_data (gdbarch, frame_base_data, table);
    }
  return table;
}