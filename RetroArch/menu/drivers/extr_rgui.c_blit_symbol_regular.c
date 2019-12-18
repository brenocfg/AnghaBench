#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  enum rgui_symbol_type { ____Placeholder_rgui_symbol_type } rgui_symbol_type ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 unsigned int FONT_HEIGHT ; 
 unsigned int FONT_WIDTH ; 
 TYPE_1__ rgui_frame_buf ; 
 int /*<<< orphan*/ * rgui_get_symbol_data (int) ; 

__attribute__((used)) static void blit_symbol_regular(unsigned fb_width, int x, int y,
      enum rgui_symbol_type symbol, uint16_t color, uint16_t shadow_color)
{
   unsigned i, j;
   uint16_t *frame_buf_data   = rgui_frame_buf.data;
   const uint8_t *symbol_data = rgui_get_symbol_data(symbol);

   if (!symbol_data)
      return;

   for (j = 0; j < FONT_HEIGHT; j++)
   {
      unsigned buff_offset = ((y + j) * fb_width) + x;

      for (i = 0; i < FONT_WIDTH; i++)
      {
         if (*symbol_data++ == 1)
            *(frame_buf_data + buff_offset + i) = color;
      }
   }
}