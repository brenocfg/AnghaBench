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
typedef  int u32 ;
typedef  int u16 ;
typedef  int s32 ;

/* Variables and functions */

s32 float_to_int(u16 f_val)
{
   u32 sign = (f_val >> 15) & 1;
   u32 sign_inverse = (!sign) & 1;
   u32 exponent = (f_val >> 11) & 0xf;
   u32 mantissa = f_val & 0x7FF;

   s32 ret_val = sign << 31;

   if (exponent > 11)
   {
      exponent = 11;
      ret_val |= (sign << 30);
   }
   else
      ret_val |= (sign_inverse << 30);

   ret_val |= mantissa << 19;

   ret_val = ret_val >> (exponent + (1 << 3));

   return ret_val;
}