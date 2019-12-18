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
typedef  scalar_t__ DOUBLEST ;

/* Variables and functions */
 int /*<<< orphan*/  builtin_type_i387_ext ; 
 scalar_t__ extract_typed_floating (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,double) ; 

__attribute__((used)) static void
print_i387_value (char *raw, struct ui_file *file)
{
  DOUBLEST value;

  /* Using extract_typed_floating here might affect the representation
     of certain numbers such as NaNs, even if GDB is running natively.
     This is fine since our caller already detects such special
     numbers and we print the hexadecimal representation anyway.  */
  value = extract_typed_floating (raw, builtin_type_i387_ext);

  /* We try to print 19 digits.  The last digit may or may not contain
     garbage, but we'd better print one too many.  We need enough room
     to print the value, 1 position for the sign, 1 for the decimal
     point, 19 for the digits and 6 for the exponent adds up to 27.  */
#ifdef PRINTF_HAS_LONG_DOUBLE
  fprintf_filtered (file, " %-+27.19Lg", (long double) value);
#else
  fprintf_filtered (file, " %-+27.19g", (double) value);
#endif
}