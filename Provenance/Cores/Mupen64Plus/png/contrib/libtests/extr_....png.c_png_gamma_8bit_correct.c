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
typedef  int /*<<< orphan*/  png_int_32 ;
typedef  double png_fixed_point ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_FP_1 ; 
 double floor (int) ; 
 int /*<<< orphan*/  png_exp8bit (double) ; 
 int /*<<< orphan*/  png_log8bit (unsigned int) ; 
 scalar_t__ png_muldiv (double*,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pow (int,double) ; 

png_byte
png_gamma_8bit_correct(unsigned int value, png_fixed_point gamma_val)
{
   if (value > 0 && value < 255)
   {
#     ifdef PNG_FLOATING_ARITHMETIC_SUPPORTED
         /* 'value' is unsigned, ANSI-C90 requires the compiler to correctly
          * convert this to a floating point value.  This includes values that
          * would overflow if 'value' were to be converted to 'int'.
          *
          * Apparently GCC, however, does an intermediate conversion to (int)
          * on some (ARM) but not all (x86) platforms, possibly because of
          * hardware FP limitations.  (E.g. if the hardware conversion always
          * assumes the integer register contains a signed value.)  This results
          * in ANSI-C undefined behavior for large values.
          *
          * Other implementations on the same machine might actually be ANSI-C90
          * conformant and therefore compile spurious extra code for the large
          * values.
          *
          * We can be reasonably sure that an unsigned to float conversion
          * won't be faster than an int to float one.  Therefore this code
          * assumes responsibility for the undefined behavior, which it knows
          * can't happen because of the check above.
          *
          * Note the argument to this routine is an (unsigned int) because, on
          * 16-bit platforms, it is assigned a value which might be out of
          * range for an (int); that would result in undefined behavior in the
          * caller if the *argument* ('value') were to be declared (int).
          */
         double r = floor(255*pow((int)/*SAFE*/value/255.,gamma_val*.00001)+.5);
         return (png_byte)r;
#     else
         png_int_32 lg2 = png_log8bit(value);
         png_fixed_point res;

         if (png_muldiv(&res, gamma_val, lg2, PNG_FP_1) != 0)
            return png_exp8bit(res);

         /* Overflow. */
         value = 0;
#     endif
   }

   return (png_byte)(value & 0xff);
}