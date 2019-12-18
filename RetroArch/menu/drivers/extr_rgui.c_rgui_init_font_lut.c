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
typedef  int uint8_t ;

/* Variables and functions */
 unsigned int FONT_HEIGHT ; 
 unsigned int FONT_OFFSET (unsigned int) ; 
 unsigned int FONT_WIDTH ; 
 unsigned int NUM_FONT_GLYPHS_EXTENDED ; 
 int* bitmap_bin ; 
 int** font_lut ; 

__attribute__((used)) static void rgui_init_font_lut(void)
{
   unsigned symbol_index, i, j;
   
   /* Loop over all possible characters */
   for (symbol_index = 0; symbol_index < NUM_FONT_GLYPHS_EXTENDED; symbol_index++)
   {
      for (j = 0; j < FONT_HEIGHT; j++)
      {
         for (i = 0; i < FONT_WIDTH; i++)
         {
            uint8_t rem = 1 << ((i + j * FONT_WIDTH) & 7);
            unsigned offset  = (i + j * FONT_WIDTH) >> 3;
            
            /* LUT value is 'true' if specified glyph position contains a pixel */
            font_lut[symbol_index][i + (j * FONT_WIDTH)] = (bitmap_bin[FONT_OFFSET(symbol_index) + offset] & rem) > 0;
         }
      }
   }
}