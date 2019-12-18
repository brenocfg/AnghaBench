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
struct dwarf2_frame_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwarf2_frame_data ; 
 struct dwarf2_frame_ops* dwarf2_frame_init (struct gdbarch*) ; 
 struct dwarf2_frame_ops* gdbarch_data (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_data (struct gdbarch*,int /*<<< orphan*/ ,struct dwarf2_frame_ops*) ; 

__attribute__((used)) static struct dwarf2_frame_ops *
dwarf2_frame_ops (struct gdbarch *gdbarch)
{
  struct dwarf2_frame_ops *ops = gdbarch_data (gdbarch, dwarf2_frame_data);
  if (ops == NULL)
    {
      /* ULGH, called during architecture initialization.  Patch
         things up.  */
      ops = dwarf2_frame_init (gdbarch);
      set_gdbarch_data (gdbarch, dwarf2_frame_data, ops);
    }
  return ops;
}