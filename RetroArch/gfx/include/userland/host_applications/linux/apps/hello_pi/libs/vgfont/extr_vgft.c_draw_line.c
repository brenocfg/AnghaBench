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
typedef  int /*<<< orphan*/  VGfloat ;
typedef  int /*<<< orphan*/  VGbitfield ;
typedef  int /*<<< orphan*/  VGFT_FONT_T ;

/* Variables and functions */
 int CHAR_COUNT_MAX ; 
 int /*<<< orphan*/  VG_GLYPH_ORIGIN ; 
 int /*<<< orphan*/  draw_chars (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vgSetfv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void draw_line(VGFT_FONT_T *font, VGfloat x, VGfloat y, const char *text, int char_count, VGbitfield paint_modes) {
   if (char_count == 0) return;

   // Set origin to requested x,y
   VGfloat glor[] = { x, y };
   vgSetfv(VG_GLYPH_ORIGIN, 2, glor);

   // Draw the characters in blocks to reuse buffer memory
   const char *curr_text = text;
   int chars_left = char_count;
   while (chars_left > CHAR_COUNT_MAX) {
      draw_chars(font, curr_text, CHAR_COUNT_MAX, paint_modes, 1);
      chars_left -= CHAR_COUNT_MAX;
      curr_text += CHAR_COUNT_MAX;
   }

   // Draw the last block
   draw_chars(font, curr_text, chars_left, paint_modes, 0);
}