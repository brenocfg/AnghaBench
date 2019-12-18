#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* store_palette ;
typedef  int /*<<< orphan*/  png_infop ;
typedef  int /*<<< orphan*/  png_const_structp ;
typedef  TYPE_2__* png_colorp ;
typedef  int* png_bytep ;
struct TYPE_7__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_6__ {int alpha; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;

/* Variables and functions */
 int PNG_INFO_PLTE ; 
 int PNG_INFO_tRNS ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 
 int png_get_PLTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,int*) ; 
 int png_get_tRNS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int**,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_palette(store_palette palette, int *npalette, png_const_structp pp,
   png_infop pi)
{
   png_colorp pal;
   png_bytep trans_alpha;
   int num;

   pal = 0;
   *npalette = -1;

   if (png_get_PLTE(pp, pi, &pal, npalette) & PNG_INFO_PLTE)
   {
      int i = *npalette;

      if (i <= 0 || i > 256)
         png_error(pp, "validate: invalid PLTE count");

      while (--i >= 0)
      {
         palette[i].red = pal[i].red;
         palette[i].green = pal[i].green;
         palette[i].blue = pal[i].blue;
      }

      /* Mark the remainder of the entries with a flag value (other than
       * white/opaque which is the flag value stored above.)
       */
      memset(palette + *npalette, 126, (256-*npalette) * sizeof *palette);
   }

   else /* !png_get_PLTE */
   {
      if (*npalette != (-1))
         png_error(pp, "validate: invalid PLTE result");
      /* But there is no palette, so record this: */
      *npalette = 0;
      memset(palette, 113, sizeof (store_palette));
   }

   trans_alpha = 0;
   num = 2; /* force error below */
   if ((png_get_tRNS(pp, pi, &trans_alpha, &num, 0) & PNG_INFO_tRNS) != 0 &&
      (trans_alpha != NULL || num != 1/*returns 1 for a transparent color*/) &&
      /* Oops, if a palette tRNS gets expanded png_read_update_info (at least so
       * far as 1.5.4) does not remove the trans_alpha pointer, only num_trans,
       * so in the above call we get a success, we get a pointer (who knows what
       * to) and we get num_trans == 0:
       */
      !(trans_alpha != NULL && num == 0)) /* TODO: fix this in libpng. */
   {
      int i;

      /* Any of these are crash-worthy - given the implementation of
       * png_get_tRNS up to 1.5 an app won't crash if it just checks the
       * result above and fails to check that the variables it passed have
       * actually been filled in!  Note that if the app were to pass the
       * last, png_color_16p, variable too it couldn't rely on this.
       */
      if (trans_alpha == NULL || num <= 0 || num > 256 || num > *npalette)
         png_error(pp, "validate: unexpected png_get_tRNS (palette) result");

      for (i=0; i<num; ++i)
         palette[i].alpha = trans_alpha[i];

      for (num=*npalette; i<num; ++i)
         palette[i].alpha = 255;

      for (; i<256; ++i)
         palette[i].alpha = 33; /* flag value */

      return 1; /* transparency */
   }

   else
   {
      /* No palette transparency - just set the alpha channel to opaque. */
      int i;

      for (i=0, num=*npalette; i<num; ++i)
         palette[i].alpha = 255;

      for (; i<256; ++i)
         palette[i].alpha = 55; /* flag value */

      return 0; /* no transparency */
   }
}