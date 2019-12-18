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
struct ui_file {int dummy; } ;
struct gdbarch {int dummy; } ;
struct frame_info {int dummy; } ;

/* Variables and functions */
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 int /*<<< orphan*/ * deprecated_selected_frame ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  float_reggroup ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 int /*<<< orphan*/  gdbarch_print_float_info (struct gdbarch*,struct ui_file*,struct frame_info*,char const*) ; 
 scalar_t__ gdbarch_print_float_info_p (struct gdbarch*) ; 
 int /*<<< orphan*/  gdbarch_print_registers_info (struct gdbarch*,struct ui_file*,struct frame_info*,int,int) ; 
 scalar_t__ gdbarch_register_reggroup_p (struct gdbarch*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_has_registers ; 

__attribute__((used)) static void
print_float_info (struct gdbarch *gdbarch, struct ui_file *file,
		  struct frame_info *frame, const char *args)
{
  if (!target_has_registers)
    error ("The program has no registers now.");
  if (deprecated_selected_frame == NULL)
    error ("No selected frame.");

  if (gdbarch_print_float_info_p (gdbarch))
    gdbarch_print_float_info (gdbarch, file, frame, args);
  else
    {
      int regnum;
      int printed_something = 0;

      for (regnum = 0; regnum < NUM_REGS + NUM_PSEUDO_REGS; regnum++)
	{
	  if (gdbarch_register_reggroup_p (gdbarch, regnum, float_reggroup))
	    {
	      printed_something = 1;
	      gdbarch_print_registers_info (gdbarch, file, frame, regnum, 1);
	    }
	}
      if (!printed_something)
	fprintf_filtered (file, "\
No floating-point info available for this processor.\n");
    }
}