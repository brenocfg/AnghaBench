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
typedef  int png_int_32 ;
typedef  int png_fixed_point ;

/* Variables and functions */
 long long PNG_UINT_31_MAX ; 
 int RAND_MAX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  png_64bit_product (long,long,unsigned long*,unsigned long*) ; 
 int png_muldiv (int*,int,int,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int rand () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbose ; 

int validation_muldiv(int count, int argc, char **argv)
{
   int tested = 0;
   int overflow = 0;
   int error = 0;
   int error64 = 0;
   int passed = 0;
   int randbits = 0;
   png_uint_32 randbuffer;
   png_fixed_point a;
   png_int_32 times, div;

   while (--argc > 0)
      {
         fprintf(stderr, "unknown argument %s\n", *++argv);
         return 1;
      }

   /* Find out about the random number generator. */
   randbuffer = RAND_MAX;
   while (randbuffer != 0) ++randbits, randbuffer >>= 1;
   printf("Using random number generator that makes %d bits\n", randbits);
   for (div=0; div<32; div += randbits)
      randbuffer = (randbuffer << randbits) ^ rand();

   a = 0;
   times = div = 0;
   do
   {
      png_fixed_point result;
      /* NOTE: your mileage may vary, a type is required below that can
       * hold 64 bits or more, if floating point is used a 64-bit or
       * better mantissa is required.
       */
      long long int fp, fpround;
      unsigned long hi, lo;
      int ok;

      /* Check the values, png_64bit_product can only handle positive
       * numbers, so correct for that here.
       */
      {
         long u1, u2;
         int n = 0;
         if (a < 0) u1 = -a, n = 1; else u1 = a;
         if (times < 0) u2 = -times, n = !n; else u2 = times;
         png_64bit_product(u1, u2, &hi, &lo);
         if (n)
         {
            /* -x = ~x+1 */
            lo = ((~lo) + 1) & 0xffffffff;
            hi = ~hi;
            if (lo == 0) ++hi;
         }
      }

      fp = a;
      fp *= times;
      if ((fp & 0xffffffff) != lo || ((fp >> 32) & 0xffffffff) != hi)
      {
         fprintf(stderr, "png_64bit_product %d * %d -> %lx|%.8lx not %llx\n",
            a, times, hi, lo, fp);
         ++error64;
      }

      if (div != 0)
      {
         /* Round - this is C round to zero. */
         if ((fp < 0) != (div < 0))
           fp -= div/2;
         else
           fp += div/2;

         fp /= div;
         fpround = fp;
         /* Assume 2's complement here: */
         ok = fpround <= PNG_UINT_31_MAX &&
              fpround >= -1-(long long int)PNG_UINT_31_MAX;
         if (!ok) ++overflow;
      }
      else
        ok = 0, ++overflow, fpround = fp/*misleading*/;

      if (verbose)
         fprintf(stderr, "TEST %d * %d / %d -> %lld (%s)\n", a, times, div,
            fp, ok ? "ok" : "overflow");

      ++tested;
      if (png_muldiv(&result, a, times, div) != ok)
      {
         ++error;
         if (ok)
             fprintf(stderr, "%d * %d / %d -> overflow (expected %lld)\n", a,
                times, div, fp);
         else
             fprintf(stderr, "%d * %d / %d -> %d (expected overflow %lld)\n", a,
                times, div, result, fp);
      }
      else if (ok && result != fpround)
      {
         ++error;
         fprintf(stderr, "%d * %d / %d -> %d not %lld\n", a, times, div, result,
            fp);
      }
      else
         ++passed;

      /* Generate three new values, this uses rand() and rand() only returns
       * up to RAND_MAX.
       */
      /* CRUDE */
      a += times;
      times += div;
      div = randbuffer;
      randbuffer = (randbuffer << randbits) ^ rand();
   }
   while (--count > 0);

   printf("%d tests including %d overflows, %d passed, %d failed (%d 64-bit "
      "errors)\n", tested, overflow, passed, error, error64);
   return 0;
}