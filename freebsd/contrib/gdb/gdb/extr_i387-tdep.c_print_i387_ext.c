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

/* Variables and functions */
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,char) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  print_i387_value (unsigned char*,struct ui_file*) ; 

__attribute__((used)) static void
print_i387_ext (unsigned char *raw, struct ui_file *file)
{
  int sign;
  int integer;
  unsigned int exponent;
  unsigned long fraction[2];

  sign = raw[9] & 0x80;
  integer = raw[7] & 0x80;
  exponent = (((raw[9] & 0x7f) << 8) | raw[8]);
  fraction[0] = ((raw[3] << 24) | (raw[2] << 16) | (raw[1] << 8) | raw[0]);
  fraction[1] = (((raw[7] & 0x7f) << 24) | (raw[6] << 16)
		 | (raw[5] << 8) | raw[4]);

  if (exponent == 0x7fff && integer)
    {
      if (fraction[0] == 0x00000000 && fraction[1] == 0x00000000)
	/* Infinity.  */
	fprintf_filtered (file, " %cInf", (sign ? '-' : '+'));
      else if (sign && fraction[0] == 0x00000000 && fraction[1] == 0x40000000)
	/* Real Indefinite (QNaN).  */
	fputs_unfiltered (" Real Indefinite (QNaN)", file);
      else if (fraction[1] & 0x40000000)
	/* QNaN.  */
	fputs_filtered (" QNaN", file);
      else
	/* SNaN.  */
	fputs_filtered (" SNaN", file);
    }
  else if (exponent < 0x7fff && exponent > 0x0000 && integer)
    /* Normal.  */
    print_i387_value (raw, file);
  else if (exponent == 0x0000)
    {
      /* Denormal or zero.  */
      print_i387_value (raw, file);
      
      if (integer)
	/* Pseudo-denormal.  */
	fputs_filtered (" Pseudo-denormal", file);
      else if (fraction[0] || fraction[1])
	/* Denormal.  */
	fputs_filtered (" Denormal", file);
    }
  else
    /* Unsupported.  */
    fputs_filtered (" Unsupported", file);
}