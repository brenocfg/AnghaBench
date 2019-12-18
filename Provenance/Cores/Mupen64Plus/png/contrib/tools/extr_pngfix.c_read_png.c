#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* global; int /*<<< orphan*/  jmpbuf; int /*<<< orphan*/  status_code; } ;
struct control {TYPE_2__ file; } ;
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  int /*<<< orphan*/ * png_structp ;
typedef  int /*<<< orphan*/ * png_infop ;
struct TYPE_3__ {scalar_t__ verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERNAL_ERROR ; 
 int LIBPNG_ERROR_CODE ; 
 int /*<<< orphan*/  PNG_LIBPNG_VER_STRING ; 
 int /*<<< orphan*/  error_handler ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_error (TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/ * png_create_info_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_create_read_struct (int /*<<< orphan*/ ,struct control*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_destroy_read_struct (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  png_get_image_height (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_row (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_chunk_cache_max (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_chunk_malloc_max (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int png_set_interlace_handling (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_read_fn (int /*<<< orphan*/ *,struct control*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_user_limits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  png_start_read_image (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_callback ; 
 int setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warning_handler ; 

__attribute__((used)) static int
read_png(struct control *control)
   /* Read a PNG, return 0 on success else an error (status) code; a bit mask as
    * defined for file::status_code as above.
    */
{
   png_structp png_ptr;
   png_infop info_ptr = NULL;
   volatile int rc;

   png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, control,
      error_handler, warning_handler);

   if (png_ptr == NULL)
   {
      /* This is not really expected. */
      log_error(&control->file, LIBPNG_ERROR_CODE, "OOM allocating png_struct");
      control->file.status_code |= INTERNAL_ERROR;
      return LIBPNG_ERROR_CODE;
   }

   rc = setjmp(control->file.jmpbuf);
   if (rc == 0)
   {
#     ifdef PNG_SET_USER_LIMITS_SUPPORTED
         /* Remove any limits on the size of PNG files that can be read,
          * without this we may reject files based on built-in safety
          * limits.
          */
         png_set_user_limits(png_ptr, 0x7fffffff, 0x7fffffff);
         png_set_chunk_cache_max(png_ptr, 0);
         png_set_chunk_malloc_max(png_ptr, 0);
#     endif

      png_set_read_fn(png_ptr, control, read_callback);

      info_ptr = png_create_info_struct(png_ptr);
      if (info_ptr == NULL)
         png_error(png_ptr, "OOM allocating info structure");

      if (control->file.global->verbose)
         fprintf(stderr, " INFO\n");

      png_read_info(png_ptr, info_ptr);

      {
        png_uint_32 height = png_get_image_height(png_ptr, info_ptr);
        int passes = png_set_interlace_handling(png_ptr);
        int pass;

        png_start_read_image(png_ptr);

        for (pass = 0; pass < passes; ++pass)
        {
           png_uint_32 y = height;

           /* NOTE: this skips asking libpng to return either version of
            * the image row, but libpng still reads the rows.
            */
           while (y-- > 0)
              png_read_row(png_ptr, NULL, NULL);
        }
      }

      if (control->file.global->verbose)
         fprintf(stderr, " END\n");

      /* Make sure to read to the end of the file: */
      png_read_end(png_ptr, info_ptr);
   }

   png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
   return rc;
}