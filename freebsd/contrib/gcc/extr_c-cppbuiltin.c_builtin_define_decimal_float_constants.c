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
typedef  int /*<<< orphan*/  tree ;
struct real_format {int p; int emin; int emax; } ;

/* Variables and functions */
 struct real_format* REAL_MODE_FORMAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_define_with_int_value (char*,int) ; 
 int /*<<< orphan*/  builtin_define_with_value (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void
builtin_define_decimal_float_constants (const char *name_prefix, 
					const char *suffix, 
					tree type)
{
  const struct real_format *fmt;
  char name[64], buf[128], *p;
  int digits;

  fmt = REAL_MODE_FORMAT (TYPE_MODE (type));

  /* The number of radix digits, p, in the significand.  */
  sprintf (name, "__%s_MANT_DIG__", name_prefix);
  builtin_define_with_int_value (name, fmt->p);

  /* The minimum negative int x such that b**(x-1) is a normalized float.  */
  sprintf (name, "__%s_MIN_EXP__", name_prefix);
  sprintf (buf, "(%d)", fmt->emin);
  builtin_define_with_value (name, buf, 0);

  /* The maximum int x such that b**(x-1) is a representable float.  */
  sprintf (name, "__%s_MAX_EXP__", name_prefix);
  builtin_define_with_int_value (name, fmt->emax);

  /* Compute the minimum representable value.  */
  sprintf (name, "__%s_MIN__", name_prefix);
  sprintf (buf, "1E%d%s", fmt->emin, suffix);
  builtin_define_with_value (name, buf, 0); 

  /* Compute the maximum representable value.  */
  sprintf (name, "__%s_MAX__", name_prefix);
  p = buf;
  for (digits = fmt->p; digits; digits--)
    {
      *p++ = '9';
      if (digits == fmt->p)
	*p++ = '.';
    }
  *p = 0;
  /* fmt->p plus 1, to account for the decimal point.  */
  sprintf (&buf[fmt->p + 1], "E%d%s", fmt->emax, suffix); 
  builtin_define_with_value (name, buf, 0);

  /* Compute epsilon (the difference between 1 and least value greater
     than 1 representable).  */
  sprintf (name, "__%s_EPSILON__", name_prefix);
  sprintf (buf, "1E-%d%s", fmt->p - 1, suffix);
  builtin_define_with_value (name, buf, 0);

  /* Minimum denormalized postive decimal value.  */
  sprintf (name, "__%s_DEN__", name_prefix);
  p = buf;
  for (digits = fmt->p; digits > 1; digits--)
    {
      *p++ = '0';
      if (digits == fmt->p)
	*p++ = '.';
    }
  *p = 0;
  sprintf (&buf[fmt->p], "1E%d%s", fmt->emin, suffix); 
  builtin_define_with_value (name, buf, 0);
}