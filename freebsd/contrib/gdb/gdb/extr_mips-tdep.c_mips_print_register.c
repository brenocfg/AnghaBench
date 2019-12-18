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
 scalar_t__ BFD_ENDIAN_BIG ; 
 int MAX_REGISTER_SIZE ; 
 int MIPS_NUMREGS ; 
 int /*<<< orphan*/  REGISTER_NAME (int) ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  frame_register_read (struct frame_info*,int,char*) ; 
 int /*<<< orphan*/  gdbarch_register_type (struct gdbarch*,int) ; 
 struct gdbarch* get_frame_arch (struct frame_info*) ; 
 int /*<<< orphan*/  mips_print_fp_register (struct ui_file*,struct frame_info*,int) ; 
 int /*<<< orphan*/  print_scalar_formatted (char*,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,struct ui_file*) ; 
 int register_size (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mips_print_register (struct ui_file *file, struct frame_info *frame,
		     int regnum, int all)
{
  struct gdbarch *gdbarch = get_frame_arch (frame);
  char raw_buffer[MAX_REGISTER_SIZE];
  int offset;

  if (TYPE_CODE (gdbarch_register_type (gdbarch, regnum)) == TYPE_CODE_FLT)
    {
      mips_print_fp_register (file, frame, regnum);
      return;
    }

  /* Get the data in raw format.  */
  if (!frame_register_read (frame, regnum, raw_buffer))
    {
      fprintf_filtered (file, "%s: [Invalid]", REGISTER_NAME (regnum));
      return;
    }

  fputs_filtered (REGISTER_NAME (regnum), file);

  /* The problem with printing numeric register names (r26, etc.) is that
     the user can't use them on input.  Probably the best solution is to
     fix it so that either the numeric or the funky (a2, etc.) names
     are accepted on input.  */
  if (regnum < MIPS_NUMREGS)
    fprintf_filtered (file, "(r%d): ", regnum);
  else
    fprintf_filtered (file, ": ");

  if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
    offset =
      register_size (current_gdbarch,
		     regnum) - register_size (current_gdbarch, regnum);
  else
    offset = 0;

  print_scalar_formatted (raw_buffer + offset,
			  gdbarch_register_type (gdbarch, regnum), 'x', 0,
			  file);
}