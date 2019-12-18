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
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 char* REGISTER_NAME (int) ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 struct gdbarch* current_gdbarch ; 
 int /*<<< orphan*/  error (char*,int,char*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  frame_register_read (struct frame_info*,int,char*) ; 
 int /*<<< orphan*/  gdbarch_register_type (struct gdbarch*,int) ; 
 struct gdbarch* get_frame_arch (struct frame_info*) ; 
 int mips_regsize (struct gdbarch*) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int register_size (struct gdbarch*,int) ; 

__attribute__((used)) static int
print_gp_register_row (struct ui_file *file, struct frame_info *frame,
		       int start_regnum)
{
  struct gdbarch *gdbarch = get_frame_arch (frame);
  /* do values for GP (int) regs */
  char raw_buffer[MAX_REGISTER_SIZE];
  int ncols = (mips_regsize (gdbarch) == 8 ? 4 : 8);	/* display cols per row */
  int col, byte;
  int regnum;

  /* For GP registers, we print a separate row of names above the vals */
  fprintf_filtered (file, "     ");
  for (col = 0, regnum = start_regnum;
       col < ncols && regnum < NUM_REGS + NUM_PSEUDO_REGS; regnum++)
    {
      if (*REGISTER_NAME (regnum) == '\0')
	continue;		/* unused register */
      if (TYPE_CODE (gdbarch_register_type (gdbarch, regnum)) ==
	  TYPE_CODE_FLT)
	break;			/* end the row: reached FP register */
      fprintf_filtered (file,
			mips_regsize (current_gdbarch) == 8 ? "%17s" : "%9s",
			REGISTER_NAME (regnum));
      col++;
    }
  /* print the R0 to R31 names */
  if ((start_regnum % NUM_REGS) < MIPS_NUMREGS)
    fprintf_filtered (file, "\n R%-4d", start_regnum % NUM_REGS);
  else
    fprintf_filtered (file, "\n      ");

  /* now print the values in hex, 4 or 8 to the row */
  for (col = 0, regnum = start_regnum;
       col < ncols && regnum < NUM_REGS + NUM_PSEUDO_REGS; regnum++)
    {
      if (*REGISTER_NAME (regnum) == '\0')
	continue;		/* unused register */
      if (TYPE_CODE (gdbarch_register_type (gdbarch, regnum)) ==
	  TYPE_CODE_FLT)
	break;			/* end row: reached FP register */
      /* OK: get the data in raw format.  */
      if (!frame_register_read (frame, regnum, raw_buffer))
	error ("can't read register %d (%s)", regnum, REGISTER_NAME (regnum));
      /* pad small registers */
      for (byte = 0;
	   byte < (mips_regsize (current_gdbarch)
		   - register_size (current_gdbarch, regnum)); byte++)
	printf_filtered ("  ");
      /* Now print the register value in hex, endian order. */
      if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
	for (byte =
	     register_size (current_gdbarch,
			    regnum) - register_size (current_gdbarch, regnum);
	     byte < register_size (current_gdbarch, regnum); byte++)
	  fprintf_filtered (file, "%02x", (unsigned char) raw_buffer[byte]);
      else
	for (byte = register_size (current_gdbarch, regnum) - 1;
	     byte >= 0; byte--)
	  fprintf_filtered (file, "%02x", (unsigned char) raw_buffer[byte]);
      fprintf_filtered (file, " ");
      col++;
    }
  if (col > 0)			/* ie. if we actually printed anything... */
    fprintf_filtered (file, "\n");

  return regnum;
}