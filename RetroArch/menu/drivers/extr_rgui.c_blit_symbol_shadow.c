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
typedef  int /*<<< orphan*/  shadow_color_buf ;
typedef  enum rgui_symbol_type { ____Placeholder_rgui_symbol_type } rgui_symbol_type ;
typedef  int /*<<< orphan*/  color_buf ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 unsigned int FONT_HEIGHT ; 
 unsigned int FONT_WIDTH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__ rgui_frame_buf ; 
 int /*<<< orphan*/ * rgui_get_symbol_data (int) ; 

__attribute__((used)) static void blit_symbol_shadow(unsigned fb_width, int x, int y,
      enum rgui_symbol_type symbol, uint16_t color, uint16_t shadow_color)
{
   unsigned i, j;
   uint16_t *frame_buf_data     = rgui_frame_buf.data;
   const uint8_t *symbol_data   = rgui_get_symbol_data(symbol);
   uint16_t color_buf[2];
   uint16_t shadow_color_buf[2];

   color_buf[0] = color;
   color_buf[1] = shadow_color;

   shadow_color_buf[0] = shadow_color;
   shadow_color_buf[1] = shadow_color;

   if (!symbol_data)
      return;

   for (j = 0; j < FONT_HEIGHT; j++)
   {
      unsigned buff_offset = ((y + j) * fb_width) + x;

      for (i = 0; i < FONT_WIDTH; i++)
      {
         if (*symbol_data++ == 1)
         {
            uint16_t *frame_buf_ptr = frame_buf_data + buff_offset + i;

            /* Symbol pixel + right shadow */
            memcpy(frame_buf_ptr, color_buf, sizeof(color_buf));

            /* Bottom shadow */
            frame_buf_ptr += fb_width;
            memcpy(frame_buf_ptr, shadow_color_buf, sizeof(shadow_color_buf));
         }
      }
   }
}