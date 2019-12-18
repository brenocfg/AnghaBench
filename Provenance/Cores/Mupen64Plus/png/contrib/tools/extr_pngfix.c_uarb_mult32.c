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
typedef  scalar_t__ uarb ;
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  png_uint_16 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int uarb_mult_digit (scalar_t__,int,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uarb_mult32(uarb acc, int a_digits, uarb num, int n_digits, png_uint_32 val)
   /* calculate acc += num * val, 'val' may be any 32-bit value, 'acc' and 'num'
    * may be any value, returns the number of digits in 'acc'.
    */
{
   if (n_digits > 0 && val > 0)
   {
      a_digits = uarb_mult_digit(acc, a_digits, num, n_digits,
         (png_uint_16)(val & 0xffff));

      val >>= 16;
      if (val > 0)
         a_digits = uarb_mult_digit(acc+1, a_digits-1, num, n_digits,
            (png_uint_16)val) + 1;

      /* Because n_digits and val are >0 the following must be true: */
      assert(a_digits > 0);
   }

   return a_digits;
}