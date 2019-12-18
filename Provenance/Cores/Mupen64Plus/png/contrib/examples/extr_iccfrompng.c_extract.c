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
typedef  int /*<<< orphan*/ * png_structp ;
typedef  int /*<<< orphan*/ * png_infop ;
typedef  int /*<<< orphan*/  png_charp ;
typedef  int /*<<< orphan*/ * png_bytep ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PNG_INFO_iCCP ; 
 int /*<<< orphan*/  PNG_LIBPNG_VER_STRING ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * no_profile ; 
 int /*<<< orphan*/ * png_create_info_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * png_create_read_struct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_destroy_read_struct (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ *,char*) ; 
 int png_get_iCCP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  png_init_io (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_jmpbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static png_bytep
extract(FILE *fp, png_uint_32 *proflen)
{
   png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);
   png_infop info_ptr = NULL;
   png_bytep result = NULL;

   /* Initialize for error or no profile: */
   *proflen = 0;

   if (png_ptr == NULL)
   {
      fprintf(stderr, "iccfrompng: version library mismatch?\n");
      return 0;
   }

   if (setjmp(png_jmpbuf(png_ptr)))
   {
      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      return 0;
   }

   png_init_io(png_ptr, fp);

   info_ptr = png_create_info_struct(png_ptr);
   if (info_ptr == NULL)
      png_error(png_ptr, "OOM allocating info structure");

   png_read_info(png_ptr, info_ptr);

   {
      png_charp name;
      int compression_type;
      png_bytep profile;

      if (png_get_iCCP(png_ptr, info_ptr, &name, &compression_type, &profile,
         proflen) & PNG_INFO_iCCP)
      {
         result = malloc(*proflen);
         if (result != NULL)
            memcpy(result, profile, *proflen);

         else
            png_error(png_ptr, "OOM allocating profile buffer");
      }

      else
	result = no_profile;
   }

   png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
   return result;
}