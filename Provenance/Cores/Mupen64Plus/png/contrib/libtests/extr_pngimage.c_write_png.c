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
struct display {char* operation; int transforms; int color_type; int /*<<< orphan*/ * write_pp; int /*<<< orphan*/  filter_method; int /*<<< orphan*/  compression_method; int /*<<< orphan*/  interlace_method; int /*<<< orphan*/  bit_depth; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  written_file; } ;
typedef  int /*<<< orphan*/  png_infop ;

/* Variables and functions */
 int /*<<< orphan*/  APP_ERROR ; 
 int PNG_COLOR_MASK_ALPHA ; 
 int /*<<< orphan*/  PNG_LIBPNG_VER_STRING ; 
 int PNG_TRANSFORM_PACKING ; 
 int PNG_TRANSFORM_STRIP_FILLER ; 
 int PNG_TRANSFORM_STRIP_FILLER_BEFORE ; 
 int /*<<< orphan*/  buffer_start_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_clean_write (struct display*) ; 
 int /*<<< orphan*/  display_error ; 
 int /*<<< orphan*/  display_log (struct display*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  display_warning ; 
 int /*<<< orphan*/ * png_create_write_struct (int /*<<< orphan*/ ,struct display*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_IHDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_user_limits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  png_set_write_fn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_write_png (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_function ; 

__attribute__((used)) static void
write_png(struct display *dp, png_infop ip, int transforms)
{
   display_clean_write(dp); /* safety */

   buffer_start_write(&dp->written_file);
   dp->operation = "write";
   dp->transforms = transforms;

   dp->write_pp = png_create_write_struct(PNG_LIBPNG_VER_STRING, dp,
      display_error, display_warning);

   if (dp->write_pp == NULL)
      display_log(dp, APP_ERROR, "failed to create write png_struct");

   png_set_write_fn(dp->write_pp, &dp->written_file, write_function,
      NULL/*flush*/);

#  ifdef PNG_SET_USER_LIMITS_SUPPORTED
      /* Remove the user limits, if any */
      png_set_user_limits(dp->write_pp, 0x7fffffff, 0x7fffffff);
#  endif

   /* Certain transforms require the png_info to be zapped to allow the
    * transform to work correctly.
    */
   if (transforms & (PNG_TRANSFORM_PACKING|
                     PNG_TRANSFORM_STRIP_FILLER|
                     PNG_TRANSFORM_STRIP_FILLER_BEFORE))
   {
      int ct = dp->color_type;

      if (transforms & (PNG_TRANSFORM_STRIP_FILLER|
                        PNG_TRANSFORM_STRIP_FILLER_BEFORE))
         ct &= ~PNG_COLOR_MASK_ALPHA;

      png_set_IHDR(dp->write_pp, ip, dp->width, dp->height, dp->bit_depth, ct,
         dp->interlace_method, dp->compression_method, dp->filter_method);
   }

   png_write_png(dp->write_pp, ip, transforms, NULL/*params*/);

   /* Clean it on the way out - if control returns to the caller then the
    * written_file contains the required data.
    */
   display_clean_write(dp);
}