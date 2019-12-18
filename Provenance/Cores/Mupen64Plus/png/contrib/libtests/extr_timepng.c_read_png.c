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
typedef  int /*<<< orphan*/ * png_structp ;
typedef  int /*<<< orphan*/  png_int_32 ;
typedef  int /*<<< orphan*/ * png_infop ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_LIBPNG_VER_STRING ; 
 int /*<<< orphan*/  no_warnings ; 
 int /*<<< orphan*/ * png_create_info_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_create_read_struct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_destroy_read_struct (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  png_init_io (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_jmpbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_png (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_benign_errors (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_by_row (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_png(FILE *fp, png_int_32 transforms, FILE *write_file)
{
   png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,
         no_warnings);
   png_infop info_ptr = NULL;

   if (png_ptr == NULL)
      return 0;

   if (setjmp(png_jmpbuf(png_ptr)))
   {
      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      return 0;
   }

#  ifdef PNG_BENIGN_ERRORS_SUPPORTED
      png_set_benign_errors(png_ptr, 1/*allowed*/);
#  endif
   png_init_io(png_ptr, fp);

   info_ptr = png_create_info_struct(png_ptr);

   if (info_ptr == NULL)
      png_error(png_ptr, "OOM allocating info structure");

   if (transforms < 0)
      read_by_row(png_ptr, info_ptr, write_file, fp);

   else
      png_read_png(png_ptr, info_ptr, transforms, NULL/*params*/);

   png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
   return 1;
}