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
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  int /*<<< orphan*/ * png_structp ;
typedef  int /*<<< orphan*/  png_size_t ;
typedef  int /*<<< orphan*/ * png_infop ;
typedef  int /*<<< orphan*/ * png_bytep ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_HANDLE_CHUNK_ALWAYS ; 
 scalar_t__ PNG_INTERLACE_ADAM7 ; 
 int PNG_INTERLACE_ADAM7_PASSES ; 
 int /*<<< orphan*/  PNG_LIBPNG_VER_STRING ; 
 int /*<<< orphan*/  PNG_PASS_ROWS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * png_create_info_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_create_read_struct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_destroy_read_struct (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  png_get_image_height (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ png_get_interlace_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_get_rowbytes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_init_io (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_jmpbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_row (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int png_set_interlace_handling (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_keep_unknown_chunks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_start_read_image (int /*<<< orphan*/ *) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_png(FILE *fp)
{
   png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);
   png_infop info_ptr = NULL;
   png_bytep row = NULL, display = NULL;

   if (png_ptr == NULL)
      return 0;

   if (setjmp(png_jmpbuf(png_ptr)))
   {
      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      if (row != NULL) free(row);
      if (display != NULL) free(display);
      return 0;
   }

   png_init_io(png_ptr, fp);

   info_ptr = png_create_info_struct(png_ptr);
   if (info_ptr == NULL)
      png_error(png_ptr, "OOM allocating info structure");

   png_set_keep_unknown_chunks(png_ptr, PNG_HANDLE_CHUNK_ALWAYS, NULL, 0);

   png_read_info(png_ptr, info_ptr);

   {
      png_size_t rowbytes = png_get_rowbytes(png_ptr, info_ptr);

      /* Failure to initialize these is harmless */
      row = malloc(rowbytes);
      display = malloc(rowbytes);

      if (row == NULL || display == NULL)
         png_error(png_ptr, "OOM allocating row buffers");

      {
         png_uint_32 height = png_get_image_height(png_ptr, info_ptr);
#        ifdef PNG_READ_INTERLACING_SUPPORTED
            int passes = png_set_interlace_handling(png_ptr);
#        else /* !READ_INTERLACING */
            int passes = png_get_interlace_type(png_ptr, info_ptr) ==
               PNG_INTERLACE_ADAM7 ? PNG_INTERLACE_ADAM7_PASSES : 1;
#        endif /* !READ_INTERLACING */
         int pass;

         png_start_read_image(png_ptr);

         for (pass = 0; pass < passes; ++pass)
         {
            png_uint_32 y = height;

#           ifndef PNG_READ_INTERLACING_SUPPORTED
               if (passes == PNG_INTERLACE_ADAM7_PASSES)
                  y = PNG_PASS_ROWS(y, pass);
#           endif /* READ_INTERLACING */

            /* NOTE: this trashes the row each time; interlace handling won't
             * work, but this avoids memory thrashing for speed testing.
             */
            while (y-- > 0)
               png_read_row(png_ptr, row, display);
         }
      }
   }

   /* Make sure to read to the end of the file: */
   png_read_end(png_ptr, info_ptr);
   png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
   free(row);
   free(display);
   return 1;
}