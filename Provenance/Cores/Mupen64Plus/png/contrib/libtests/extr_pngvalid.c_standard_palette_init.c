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
struct TYPE_6__ {int alpha; } ;
typedef  TYPE_1__ store_palette_entry ;
struct TYPE_7__ {int npalette; int is_transparent; int /*<<< orphan*/  palette; int /*<<< orphan*/  ps; } ;
typedef  TYPE_2__ standard_display ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 TYPE_1__* store_current_palette (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
standard_palette_init(standard_display *dp)
{
   store_palette_entry *palette = store_current_palette(dp->ps, &dp->npalette);

   /* The remaining entries remain white/opaque. */
   if (dp->npalette > 0)
   {
      int i = dp->npalette;
      memcpy(dp->palette, palette, i * sizeof *palette);

      /* Check for a non-opaque palette entry: */
      while (--i >= 0)
         if (palette[i].alpha < 255)
            break;

#     ifdef __GNUC__
         /* GCC can't handle the more obviously optimizable version. */
         if (i >= 0)
            dp->is_transparent = 1;
         else
            dp->is_transparent = 0;
#     else
         dp->is_transparent = (i >= 0);
#     endif
   }
}