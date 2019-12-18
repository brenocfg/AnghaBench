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
typedef  long png_uint_32 ;
typedef  int /*<<< orphan*/ * png_structp ;
typedef  int /*<<< orphan*/ * png_infop ;
typedef  int /*<<< orphan*/ * png_bytep ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  PNG_INTERLACE_ADAM7 129 
 int PNG_INTERLACE_ADAM7_PASSES ; 
#define  PNG_INTERLACE_NONE 128 
 int /*<<< orphan*/  PNG_LIBPNG_VER_STRING ; 
 scalar_t__ PNG_PASS_COLS (long,int) ; 
 long PNG_PASS_COL_OFFSET (int) ; 
 long PNG_PASS_ROW_OFFSET (int) ; 
 long PNG_PASS_START_COL (int) ; 
 long PNG_PASS_START_ROW (int) ; 
 long atol (char const*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * png_create_info_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_create_read_struct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_destroy_info_struct (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  png_destroy_read_struct (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  png_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ png_get_IHDR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long*,long*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  png_get_rowbytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_init_io (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_jmpbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_read_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_row (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_start_read_image (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_pixel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, const char **argv)
{
   /* This program uses the default, <setjmp.h> based, libpng error handling
    * mechanism, therefore any local variable that exists before the call to
    * setjmp and is changed after the call to setjmp returns successfully must
    * be declared with 'volatile' to ensure that their values don't get
    * destroyed by longjmp:
    */
   volatile int result = 1/*fail*/;

   if (argc == 4)
   {
      long x = atol(argv[1]);
      long y = atol(argv[2]);
      FILE *f = fopen(argv[3], "rb");
      volatile png_bytep row = NULL;

      if (f != NULL)
      {
         /* libpng requires a callback function for handling errors; this
          * callback must not return.  The default callback function uses a
          * stored <setjmp.h> style jmp_buf which is held in a png_struct and
          * writes error messages to stderr.  Creating the png_struct is a
          * little tricky; just copy the following code.
          */
         png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
            NULL, NULL, NULL);

         if (png_ptr != NULL)
         {
            png_infop info_ptr = png_create_info_struct(png_ptr);

            if (info_ptr != NULL)
            {
               /* Declare stack variables to hold pointers to locally allocated
                * data.
                */

               /* Initialize the error control buffer: */
               if (setjmp(png_jmpbuf(png_ptr)) == 0)
               {
                  png_uint_32 width, height;
                  int bit_depth, color_type, interlace_method,
                     compression_method, filter_method;
                  png_bytep row_tmp;

                  /* Now associate the recently opened (FILE*) with the default
                   * libpng initialization functions.  Sometimes libpng is
                   * compiled without stdio support (it can be difficult to do
                   * in some environments); in that case you will have to write
                   * your own read callback to read data from the (FILE*).
                   */
                  png_init_io(png_ptr, f);

                  /* And read the first part of the PNG file - the header and
                   * all the information up to the first pixel.
                   */
                  png_read_info(png_ptr, info_ptr);

                  /* This fills in enough information to tell us the width of
                   * each row in bytes, allocate the appropriate amount of
                   * space.  In this case png_malloc is used - it will not
                   * return if memory isn't available.
                   */
                  row = png_malloc(png_ptr, png_get_rowbytes(png_ptr,
                     info_ptr));

                  /* To avoid the overhead of using a volatile auto copy row_tmp
                   * to a local here - just use row for the png_free below.
                   */
                  row_tmp = row;

                  /* All the information we need is in the header is returned by
                   * png_get_IHDR, if this fails we can now use 'png_error' to
                   * signal the error and return control to the setjmp above.
                   */
                  if (png_get_IHDR(png_ptr, info_ptr, &width, &height,
                     &bit_depth, &color_type, &interlace_method,
                     &compression_method, &filter_method))
                  {
                     int passes, pass;

                     /* png_set_interlace_handling returns the number of
                      * passes required as well as turning on libpng's
                      * handling, but since we do it ourselves this is
                      * necessary:
                      */
                     switch (interlace_method)
                     {
                        case PNG_INTERLACE_NONE:
                           passes = 1;
                           break;

                        case PNG_INTERLACE_ADAM7:
                           passes = PNG_INTERLACE_ADAM7_PASSES;
                           break;

                        default:
                           png_error(png_ptr, "pngpixel: unknown interlace");
                     }

                     /* Now read the pixels, pass-by-pass, row-by-row: */
                     png_start_read_image(png_ptr);

                     for (pass=0; pass<passes; ++pass)
                     {
                        png_uint_32 ystart, xstart, ystep, xstep;
                        png_uint_32 py;

                        if (interlace_method == PNG_INTERLACE_ADAM7)
                        {
                           /* Sometimes the whole pass is empty because the
                            * image is too narrow or too short.  libpng
                            * expects to be called for each row that is
                            * present in the pass, so it may be necessary to
                            * skip the loop below (over py) if the image is
                            * too narrow.
                            */
                           if (PNG_PASS_COLS(width, pass) == 0)
                              continue;

                           /* We need the starting pixel and the offset
                            * between each pixel in this pass; use the macros
                            * in png.h:
                            */
                           xstart = PNG_PASS_START_COL(pass);
                           ystart = PNG_PASS_START_ROW(pass);
                           xstep = PNG_PASS_COL_OFFSET(pass);
                           ystep = PNG_PASS_ROW_OFFSET(pass);
                        }

                        else
                        {
                           ystart = xstart = 0;
                           ystep = xstep = 1;
                        }

                        /* To find the pixel, loop over 'py' for each pass
                         * reading a row and then checking to see if it
                         * contains the pixel.
                         */
                        for (py = ystart; py < height; py += ystep)
                        {
                           png_uint_32 px, ppx;

                           /* png_read_row takes two pointers.  When libpng
                            * handles the interlace the first is filled in
                            * pixel-by-pixel, and the second receives the same
                            * pixels but they are replicated across the
                            * unwritten pixels so far for each pass.  When we
                            * do the interlace, however, they just contain
                            * the pixels from the interlace pass - giving
                            * both is wasteful and pointless, so we pass a
                            * NULL pointer.
                            */
                           png_read_row(png_ptr, row_tmp, NULL);

                           /* Now find the pixel if it is in this row; there
                            * are, of course, much better ways of doing this
                            * than using a for loop:
                            */
                           if (y == py) for (px = xstart, ppx = 0;
                              px < width; px += xstep, ++ppx) if (x == px)
                           {
                              /* 'ppx' is the index of the pixel in the row
                               * buffer.
                               */
                              print_pixel(png_ptr, info_ptr, row_tmp, ppx);

                              /* Now terminate the loops early - we have
                               * found and handled the required data.
                               */
                              goto pass_loop_end;
                           } /* x loop */
                        } /* y loop */
                     } /* pass loop */

                     /* Finally free the temporary buffer: */
                  pass_loop_end:
                     row = NULL;
                     png_free(png_ptr, row_tmp);
                  }

                  else
                     png_error(png_ptr, "pngpixel: png_get_IHDR failed");

               }

               else
               {
                  /* Else libpng has raised an error.  An error message has
                   * already been output, so it is only necessary to clean up
                   * locally allocated data:
                   */
                  if (row != NULL)
                  {
                     /* The default implementation of png_free never errors out
                      * (it just crashes if something goes wrong), but the safe
                      * way of using it is still to clear 'row' before calling
                      * png_free:
                      */
                     png_bytep row_tmp = row;
                     row = NULL;
                     png_free(png_ptr, row_tmp);
                  }
               }

               png_destroy_info_struct(png_ptr, &info_ptr);
            }

            else
               fprintf(stderr, "pngpixel: out of memory allocating png_info\n");

            png_destroy_read_struct(&png_ptr, NULL, NULL);
         }

         else
            fprintf(stderr, "pngpixel: out of memory allocating png_struct\n");
      }

      else
         fprintf(stderr, "pngpixel: %s: could not open file\n", argv[3]);
   }

   else
      /* Wrong number of arguments */
      fprintf(stderr, "pngpixel: usage: pngpixel x y png-file\n");

   return result;
}