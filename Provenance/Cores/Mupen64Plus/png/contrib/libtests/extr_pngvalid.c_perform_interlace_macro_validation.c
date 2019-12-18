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
typedef  scalar_t__ png_uint_32 ;

/* Variables and functions */
 scalar_t__ PNG_COL_FROM_PASS_COL (scalar_t__,int) ; 
 scalar_t__ PNG_COL_IN_INTERLACE_PASS (scalar_t__,int) ; 
 scalar_t__ PNG_PASS_COLS (scalar_t__,int) ; 
 scalar_t__ PNG_PASS_COL_SHIFT (int) ; 
 scalar_t__ PNG_PASS_ROWS (scalar_t__,int) ; 
 scalar_t__ PNG_PASS_ROW_SHIFT (int) ; 
 scalar_t__ PNG_PASS_START_COL (int) ; 
 scalar_t__ PNG_PASS_START_ROW (int) ; 
 scalar_t__ PNG_ROW_FROM_PASS_ROW (scalar_t__,int) ; 
 scalar_t__ PNG_ROW_IN_INTERLACE_PASS (scalar_t__,int) ; 
 scalar_t__ PNG_UINT_31_MAX ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,int,scalar_t__,...) ; 
 scalar_t__ png_col_from_pass_col (scalar_t__,int) ; 
 scalar_t__ png_col_in_interlace_pass (scalar_t__,int) ; 
 scalar_t__ png_pass_col_shift (int) ; 
 scalar_t__ png_pass_cols (scalar_t__,int) ; 
 scalar_t__ png_pass_row_shift (int) ; 
 scalar_t__ png_pass_rows (scalar_t__,int) ; 
 scalar_t__ png_pass_start_col (int) ; 
 scalar_t__ png_pass_start_row (int) ; 
 scalar_t__ png_row_from_pass_row (scalar_t__,int) ; 
 scalar_t__ png_row_in_interlace_pass (scalar_t__,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
perform_interlace_macro_validation(void)
{
   /* The macros to validate, first those that depend only on pass:
    *
    * PNG_PASS_START_ROW(pass)
    * PNG_PASS_START_COL(pass)
    * PNG_PASS_ROW_SHIFT(pass)
    * PNG_PASS_COL_SHIFT(pass)
    */
   int pass;

   for (pass=0; pass<7; ++pass)
   {
      png_uint_32 m, f, v;

      m = PNG_PASS_START_ROW(pass);
      f = png_pass_start_row(pass);
      if (m != f)
      {
         fprintf(stderr, "PNG_PASS_START_ROW(%d) = %u != %x\n", pass, m, f);
         exit(99);
      }

      m = PNG_PASS_START_COL(pass);
      f = png_pass_start_col(pass);
      if (m != f)
      {
         fprintf(stderr, "PNG_PASS_START_COL(%d) = %u != %x\n", pass, m, f);
         exit(99);
      }

      m = PNG_PASS_ROW_SHIFT(pass);
      f = png_pass_row_shift(pass);
      if (m != f)
      {
         fprintf(stderr, "PNG_PASS_ROW_SHIFT(%d) = %u != %x\n", pass, m, f);
         exit(99);
      }

      m = PNG_PASS_COL_SHIFT(pass);
      f = png_pass_col_shift(pass);
      if (m != f)
      {
         fprintf(stderr, "PNG_PASS_COL_SHIFT(%d) = %u != %x\n", pass, m, f);
         exit(99);
      }

      /* Macros that depend on the image or sub-image height too:
       *
       * PNG_PASS_ROWS(height, pass)
       * PNG_PASS_COLS(width, pass)
       * PNG_ROW_FROM_PASS_ROW(yIn, pass)
       * PNG_COL_FROM_PASS_COL(xIn, pass)
       * PNG_ROW_IN_INTERLACE_PASS(y, pass)
       * PNG_COL_IN_INTERLACE_PASS(x, pass)
       */
      for (v=0;;)
      {
         /* The first two tests overflow if the pass row or column is outside
          * the possible range for a 32-bit result.  In fact the values should
          * never be outside the range for a 31-bit result, but checking for 32
          * bits here ensures that if an app uses a bogus pass row or column
          * (just so long as it fits in a 32 bit integer) it won't get a
          * possibly dangerous overflow.
          */
         /* First the base 0 stuff: */
         if (v < png_pass_rows(0xFFFFFFFFU, pass))
         {
            m = PNG_ROW_FROM_PASS_ROW(v, pass);
            f = png_row_from_pass_row(v, pass);
            if (m != f)
            {
               fprintf(stderr, "PNG_ROW_FROM_PASS_ROW(%u, %d) = %u != %x\n",
                  v, pass, m, f);
               exit(99);
            }
         }

         if (v < png_pass_cols(0xFFFFFFFFU, pass))
         {
            m = PNG_COL_FROM_PASS_COL(v, pass);
            f = png_col_from_pass_col(v, pass);
            if (m != f)
            {
               fprintf(stderr, "PNG_COL_FROM_PASS_COL(%u, %d) = %u != %x\n",
                  v, pass, m, f);
               exit(99);
            }
         }

         m = PNG_ROW_IN_INTERLACE_PASS(v, pass);
         f = png_row_in_interlace_pass(v, pass);
         if (m != f)
         {
            fprintf(stderr, "PNG_ROW_IN_INTERLACE_PASS(%u, %d) = %u != %x\n",
               v, pass, m, f);
            exit(99);
         }

         m = PNG_COL_IN_INTERLACE_PASS(v, pass);
         f = png_col_in_interlace_pass(v, pass);
         if (m != f)
         {
            fprintf(stderr, "PNG_COL_IN_INTERLACE_PASS(%u, %d) = %u != %x\n",
               v, pass, m, f);
            exit(99);
         }

         /* Then the base 1 stuff: */
         ++v;
         m = PNG_PASS_ROWS(v, pass);
         f = png_pass_rows(v, pass);
         if (m != f)
         {
            fprintf(stderr, "PNG_PASS_ROWS(%u, %d) = %u != %x\n",
               v, pass, m, f);
            exit(99);
         }

         m = PNG_PASS_COLS(v, pass);
         f = png_pass_cols(v, pass);
         if (m != f)
         {
            fprintf(stderr, "PNG_PASS_COLS(%u, %d) = %u != %x\n",
               v, pass, m, f);
            exit(99);
         }

         /* Move to the next v - the stepping algorithm starts skipping
          * values above 1024.
          */
         if (v > 1024)
         {
            if (v == PNG_UINT_31_MAX)
               break;

            v = (v << 1) ^ v;
            if (v >= PNG_UINT_31_MAX)
               v = PNG_UINT_31_MAX-1;
         }
      }
   }
}