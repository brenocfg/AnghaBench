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
struct TYPE_5__ {int red; int green; int blue; int alpha; } ;
typedef  TYPE_1__ store_palette_entry ;
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_store ;
typedef  int /*<<< orphan*/  png_infop ;
struct TYPE_6__ {int red; int green; int blue; } ;
typedef  TYPE_2__ png_color ;
typedef  int png_byte ;

/* Variables and functions */
 TYPE_1__* make_standard_palette (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  png_set_PLTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  png_set_tRNS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_standard_palette(png_store *ps, png_structp pp, png_infop pi, int npalette,
   int do_tRNS)
{
   store_palette_entry *ppal = make_standard_palette(ps, npalette, do_tRNS);

   {
      int i;
      png_color palette[256];

      /* Set all entries to detect overread errors. */
      for (i=0; i<npalette; ++i)
      {
         palette[i].red = ppal[i].red;
         palette[i].green = ppal[i].green;
         palette[i].blue = ppal[i].blue;
      }

      /* Just in case fill in the rest with detectable values: */
      for (; i<256; ++i)
         palette[i].red = palette[i].green = palette[i].blue = 42;

      png_set_PLTE(pp, pi, palette, npalette);
   }

   if (do_tRNS)
   {
      int i, j;
      png_byte tRNS[256];

      /* Set all the entries, but skip trailing opaque entries */
      for (i=j=0; i<npalette; ++i)
         if ((tRNS[i] = ppal[i].alpha) < 255)
            j = i+1;

      /* Fill in the remainder with a detectable value: */
      for (; i<256; ++i)
         tRNS[i] = 24;

#ifdef PNG_WRITE_tRNS_SUPPORTED
      if (j > 0)
         png_set_tRNS(pp, pi, tRNS, j, 0/*color*/);
#endif
   }
}