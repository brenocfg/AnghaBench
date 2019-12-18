#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VGfloat ;
typedef  int /*<<< orphan*/  VGbitfield ;
struct TYPE_10__ {TYPE_2__* ft_face; } ;
typedef  TYPE_4__ VGFT_FONT_T ;
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  descender; } ;
struct TYPE_8__ {TYPE_1__* size; } ;
struct TYPE_7__ {TYPE_3__ metrics; } ;

/* Variables and functions */
 int /*<<< orphan*/  draw_line (TYPE_4__*,scalar_t__,scalar_t__,char const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ float_from_26_6 (int /*<<< orphan*/ ) ; 

void vgft_font_draw(VGFT_FONT_T *font, VGfloat x, VGfloat y, const char *text, unsigned text_length, VGbitfield paint_modes)
{
   VGfloat descent = float_from_26_6(font->ft_face->size->metrics.descender);
   int last_draw = 0;
   int i = 0;
   y -= descent;
   for (;;) {
      int last = !text[i] || (text_length && i==text_length);

      if ((text[i] == '\n') || last)
      {
         draw_line(font, x, y, text + last_draw, i - last_draw, paint_modes);
         last_draw = i+1;
         y -= float_from_26_6(font->ft_face->size->metrics.height);
      }
      if (last)
      {
         break;
      }
      ++i;
   }
}