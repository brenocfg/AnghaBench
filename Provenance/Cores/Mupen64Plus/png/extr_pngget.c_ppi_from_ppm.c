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
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  png_int_32 ;
typedef  int /*<<< orphan*/  png_fixed_point ;

/* Variables and functions */
 int PNG_UINT_31_MAX ; 
 scalar_t__ png_muldiv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static png_uint_32
ppi_from_ppm(png_uint_32 ppm)
{
#if 0
   /* The conversion is *(2.54/100), in binary (32 digits):
    * .00000110100000001001110101001001
    */
   png_uint_32 t1001, t1101;
   ppm >>= 1;                  /* .1 */
   t1001 = ppm + (ppm >> 3);   /* .1001 */
   t1101 = t1001 + (ppm >> 1); /* .1101 */
   ppm >>= 20;                 /* .000000000000000000001 */
   t1101 += t1101 >> 15;       /* .1101000000000001101 */
   t1001 >>= 11;               /* .000000000001001 */
   t1001 += t1001 >> 12;       /* .000000000001001000000001001 */
   ppm += t1001;               /* .000000000001001000001001001 */
   ppm += t1101;               /* .110100000001001110101001001 */
   return (ppm + 16) >> 5;/* .00000110100000001001110101001001 */
#else
   /* The argument is a PNG unsigned integer, so it is not permitted
    * to be bigger than 2^31.
    */
   png_fixed_point result;
   if (ppm <= PNG_UINT_31_MAX && png_muldiv(&result, (png_int_32)ppm, 127,
       5000) != 0)
      return (png_uint_32)result;

   /* Overflow. */
   return 0;
#endif
}