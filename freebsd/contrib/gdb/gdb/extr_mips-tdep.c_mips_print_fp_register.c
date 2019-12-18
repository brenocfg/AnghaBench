#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ui_file {int dummy; } ;
struct frame_info {int dummy; } ;
struct TYPE_2__ {int fp0; } ;

/* Variables and functions */
 double REGISTER_NAME (int) ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  builtin_type_uint32 ; 
 int /*<<< orphan*/  builtin_type_uint64 ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 scalar_t__ mips2_fp_compat () ; 
 int /*<<< orphan*/  mips_double_register_type () ; 
 int /*<<< orphan*/  mips_float_register_type () ; 
 int /*<<< orphan*/  mips_read_fp_register_double (struct frame_info*,int,char*) ; 
 int /*<<< orphan*/  mips_read_fp_register_single (struct frame_info*,int,char*) ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_scalar_formatted (char*,int /*<<< orphan*/ ,char,char,struct ui_file*) ; 
 int register_size (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (double) ; 
 double unpack_double (int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static void
mips_print_fp_register (struct ui_file *file, struct frame_info *frame,
			int regnum)
{				/* do values for FP (float) regs */
  char *raw_buffer;
  double doub, flt1;	/* doubles extracted from raw hex data */
  int inv1, inv2;

  raw_buffer =
    (char *) alloca (2 *
		     register_size (current_gdbarch,
				    mips_regnum (current_gdbarch)->fp0));

  fprintf_filtered (file, "%s:", REGISTER_NAME (regnum));
  fprintf_filtered (file, "%*s", 4 - (int) strlen (REGISTER_NAME (regnum)),
		    "");

  if (register_size (current_gdbarch, regnum) == 4 || mips2_fp_compat ())
    {
      /* 4-byte registers: Print hex and floating.  Also print even
         numbered registers as doubles.  */
      mips_read_fp_register_single (frame, regnum, raw_buffer);
      flt1 = unpack_double (mips_float_register_type (), raw_buffer, &inv1);

      print_scalar_formatted (raw_buffer, builtin_type_uint32, 'x', 'w',
			      file);

      fprintf_filtered (file, " flt: ");
      if (inv1)
	fprintf_filtered (file, " <invalid float> ");
      else
	fprintf_filtered (file, "%-17.9g", flt1);

      if (regnum % 2 == 0)
	{
	  mips_read_fp_register_double (frame, regnum, raw_buffer);
	  doub = unpack_double (mips_double_register_type (), raw_buffer,
				&inv2);

	  fprintf_filtered (file, " dbl: ");
	  if (inv2)
	    fprintf_filtered (file, "<invalid double>");
	  else
	    fprintf_filtered (file, "%-24.17g", doub);
	}
    }
  else
    {
      /* Eight byte registers: print each one as hex, float and double.  */
      mips_read_fp_register_single (frame, regnum, raw_buffer);
      flt1 = unpack_double (mips_float_register_type (), raw_buffer, &inv1);

      mips_read_fp_register_double (frame, regnum, raw_buffer);
      doub = unpack_double (mips_double_register_type (), raw_buffer, &inv2);


      print_scalar_formatted (raw_buffer, builtin_type_uint64, 'x', 'g',
			      file);

      fprintf_filtered (file, " flt: ");
      if (inv1)
	fprintf_filtered (file, "<invalid float>");
      else
	fprintf_filtered (file, "%-17.9g", flt1);

      fprintf_filtered (file, " dbl: ");
      if (inv2)
	fprintf_filtered (file, "<invalid double>");
      else
	fprintf_filtered (file, "%-24.17g", doub);
    }
}