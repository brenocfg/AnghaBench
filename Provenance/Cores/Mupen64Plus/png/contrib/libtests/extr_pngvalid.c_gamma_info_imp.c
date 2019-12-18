#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_infop ;
typedef  int /*<<< orphan*/  const png_fixed_point ;
struct TYPE_6__ {int use_update_info; } ;
struct TYPE_5__ {int do_background; double screen_gamma; double const file_gamma; double background_gamma; TYPE_2__ this; int /*<<< orphan*/  background_color; scalar_t__ expand16; scalar_t__ scale16; } ;
typedef  TYPE_1__ gamma_display ;

/* Variables and functions */
 int ALPHA_MODE_OFFSET ; 
 int PNG_ALPHA_STANDARD ; 
 int /*<<< orphan*/  const fix (double const) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  png_read_update_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_alpha_mode (int /*<<< orphan*/ ,int,double const) ; 
 int /*<<< orphan*/  png_set_alpha_mode_fixed (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  png_set_background (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,double const) ; 
 int /*<<< orphan*/  png_set_background_fixed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  png_set_expand_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_gamma (int /*<<< orphan*/ ,double const,double const) ; 
 int /*<<< orphan*/  png_set_gamma_fixed (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  png_set_scale_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_set_strip_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  standard_info_part1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  standard_info_part2 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
gamma_info_imp(gamma_display *dp, png_structp pp, png_infop pi)
{
   /* Reuse the standard stuff as appropriate. */
   standard_info_part1(&dp->this, pp, pi);

   /* If requested strip 16 to 8 bits - this is handled automagically below
    * because the output bit depth is read from the library.  Note that there
    * are interactions with sBIT but, internally, libpng makes sbit at most
    * PNG_MAX_GAMMA_8 prior to 1.7 when doing the following.
    */
   if (dp->scale16)
#     ifdef PNG_READ_SCALE_16_TO_8_SUPPORTED
         png_set_scale_16(pp);
#     else
         /* The following works both in 1.5.4 and earlier versions: */
#        ifdef PNG_READ_16_TO_8_SUPPORTED
            png_set_strip_16(pp);
#        else
            png_error(pp, "scale16 (16 to 8 bit conversion) not supported");
#        endif
#     endif

   if (dp->expand16)
#     ifdef PNG_READ_EXPAND_16_SUPPORTED
         png_set_expand_16(pp);
#     else
         png_error(pp, "expand16 (8 to 16 bit conversion) not supported");
#     endif

   if (dp->do_background >= ALPHA_MODE_OFFSET)
   {
#     ifdef PNG_READ_ALPHA_MODE_SUPPORTED
      {
         /* This tests the alpha mode handling, if supported. */
         int mode = dp->do_background - ALPHA_MODE_OFFSET;

         /* The gamma value is the output gamma, and is in the standard,
          * non-inverted, represenation.  It provides a default for the PNG file
          * gamma, but since the file has a gAMA chunk this does not matter.
          */
         const double sg = dp->screen_gamma;
#        ifndef PNG_FLOATING_POINT_SUPPORTED
            const png_fixed_point g = fix(sg);
#        endif

#        ifdef PNG_FLOATING_POINT_SUPPORTED
            png_set_alpha_mode(pp, mode, sg);
#        else
            png_set_alpha_mode_fixed(pp, mode, g);
#        endif

         /* However, for the standard Porter-Duff algorithm the output defaults
          * to be linear, so if the test requires non-linear output it must be
          * corrected here.
          */
         if (mode == PNG_ALPHA_STANDARD && sg != 1)
         {
#           ifdef PNG_FLOATING_POINT_SUPPORTED
               png_set_gamma(pp, sg, dp->file_gamma);
#           else
               png_fixed_point f = fix(dp->file_gamma);
               png_set_gamma_fixed(pp, g, f);
#           endif
         }
      }
#     else
         png_error(pp, "alpha mode handling not supported");
#     endif
   }

   else
   {
      /* Set up gamma processing. */
#     ifdef PNG_FLOATING_POINT_SUPPORTED
         png_set_gamma(pp, dp->screen_gamma, dp->file_gamma);
#     else
      {
         png_fixed_point s = fix(dp->screen_gamma);
         png_fixed_point f = fix(dp->file_gamma);
         png_set_gamma_fixed(pp, s, f);
      }
#     endif

      if (dp->do_background)
      {
#     ifdef PNG_READ_BACKGROUND_SUPPORTED
         /* NOTE: this assumes the caller provided the correct background gamma!
          */
         const double bg = dp->background_gamma;
#        ifndef PNG_FLOATING_POINT_SUPPORTED
            const png_fixed_point g = fix(bg);
#        endif

#        ifdef PNG_FLOATING_POINT_SUPPORTED
            png_set_background(pp, &dp->background_color, dp->do_background,
               0/*need_expand*/, bg);
#        else
            png_set_background_fixed(pp, &dp->background_color,
               dp->do_background, 0/*need_expand*/, g);
#        endif
#     else
         png_error(pp, "png_set_background not supported");
#     endif
      }
   }

   {
      int i = dp->this.use_update_info;
      /* Always do one call, even if use_update_info is 0. */
      do
         png_read_update_info(pp, pi);
      while (--i > 0);
   }

   /* Now we may get a different cbRow: */
   standard_info_part2(&dp->this, pp, pi, 1 /*images*/);
}