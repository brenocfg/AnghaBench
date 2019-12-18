#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ vg_font; scalar_t__ ft_face; } ;
typedef  TYPE_1__ VGFT_FONT_T ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_Face (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vgDestroyFont (scalar_t__) ; 

void vgft_font_term(VGFT_FONT_T *font)
{
   if (font->ft_face)
      FT_Done_Face(font->ft_face);
   if (font->vg_font)
      vgDestroyFont(font->vg_font);
   memset(font, 0, sizeof(*font));
}