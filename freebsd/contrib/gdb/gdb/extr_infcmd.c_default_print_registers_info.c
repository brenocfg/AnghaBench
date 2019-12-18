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
 int /*<<< orphan*/  DEPRECATED_DO_REGISTERS_INFO (int,int) ; 
 scalar_t__ DEPRECATED_DO_REGISTERS_INFO_P () ; 
 scalar_t__ DEPRECATED_REGISTER_CONVERTIBLE (int) ; 
 scalar_t__ DEPRECATED_REGISTER_CONVERTIBLE_P () ; 
 int /*<<< orphan*/  DEPRECATED_REGISTER_CONVERT_TO_VIRTUAL (int,int /*<<< orphan*/ ,char*,char*) ; 
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int /*<<< orphan*/  DEPRECATED_REGISTER_VIRTUAL_SIZE (int) ; 
 int MAX_REGISTER_SIZE ; 
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 char* REGISTER_NAME (int) ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 scalar_t__ TYPE_VECTOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Val_pretty_default ; 
 int /*<<< orphan*/  all_reggroup ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  frame_register_read (struct frame_info*,int,char*) ; 
 int /*<<< orphan*/  gdbarch_register_reggroup_p (struct gdbarch*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  general_reggroup ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_spaces_filtered (scalar_t__,struct ui_file*) ; 
 int /*<<< orphan*/  register_type (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  val_print (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ui_file*,char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
default_print_registers_info (struct gdbarch *gdbarch,
			      struct ui_file *file,
			      struct frame_info *frame,
			      int regnum, int print_all)
{
  int i;
  const int numregs = NUM_REGS + NUM_PSEUDO_REGS;
  char raw_buffer[MAX_REGISTER_SIZE];
  char virtual_buffer[MAX_REGISTER_SIZE];

  if (DEPRECATED_DO_REGISTERS_INFO_P ())
    {
      DEPRECATED_DO_REGISTERS_INFO (regnum, print_all);
      return;
    }

  for (i = 0; i < numregs; i++)
    {
      /* Decide between printing all regs, non-float / vector regs, or
         specific reg.  */
      if (regnum == -1)
	{
	  if (print_all)
	    {
	      if (!gdbarch_register_reggroup_p (gdbarch, i, all_reggroup))
		continue;
	    }
	  else
	    {
	      if (!gdbarch_register_reggroup_p (gdbarch, i, general_reggroup))
		continue;
	    }
	}
      else
	{
	  if (i != regnum)
	    continue;
	}

      /* If the register name is empty, it is undefined for this
         processor, so don't display anything.  */
      if (REGISTER_NAME (i) == NULL || *(REGISTER_NAME (i)) == '\0')
	continue;

      fputs_filtered (REGISTER_NAME (i), file);
      print_spaces_filtered (15 - strlen (REGISTER_NAME (i)), file);

      /* Get the data in raw format.  */
      if (! frame_register_read (frame, i, raw_buffer))
	{
	  fprintf_filtered (file, "*value not available*\n");
	  continue;
	}

      /* FIXME: cagney/2002-08-03: This code shouldn't be necessary.
         The function frame_register_read() should have returned the
         pre-cooked register so no conversion is necessary.  */
      /* Convert raw data to virtual format if necessary.  */
      if (DEPRECATED_REGISTER_CONVERTIBLE_P ()
	  && DEPRECATED_REGISTER_CONVERTIBLE (i))
	{
	  DEPRECATED_REGISTER_CONVERT_TO_VIRTUAL (i, register_type (current_gdbarch, i),
				       raw_buffer, virtual_buffer);
	}
      else
	{
	  memcpy (virtual_buffer, raw_buffer,
		  DEPRECATED_REGISTER_VIRTUAL_SIZE (i));
	}

      /* If virtual format is floating, print it that way, and in raw
         hex.  */
      if (TYPE_CODE (register_type (current_gdbarch, i)) == TYPE_CODE_FLT)
	{
	  int j;

	  val_print (register_type (current_gdbarch, i), virtual_buffer, 0, 0,
		     file, 0, 1, 0, Val_pretty_default);

	  fprintf_filtered (file, "\t(raw 0x");
	  for (j = 0; j < DEPRECATED_REGISTER_RAW_SIZE (i); j++)
	    {
	      int idx;
	      if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
		idx = j;
	      else
		idx = DEPRECATED_REGISTER_RAW_SIZE (i) - 1 - j;
	      fprintf_filtered (file, "%02x", (unsigned char) raw_buffer[idx]);
	    }
	  fprintf_filtered (file, ")");
	}
      else
	{
	  /* Print the register in hex.  */
	  val_print (register_type (current_gdbarch, i), virtual_buffer, 0, 0,
		     file, 'x', 1, 0, Val_pretty_default);
          /* If not a vector register, print it also according to its
             natural format.  */
	  if (TYPE_VECTOR (register_type (current_gdbarch, i)) == 0)
	    {
	      fprintf_filtered (file, "\t");
	      val_print (register_type (current_gdbarch, i), virtual_buffer, 0, 0,
			 file, 0, 1, 0, Val_pretty_default);
	    }
	}

      fprintf_filtered (file, "\n");
    }
}