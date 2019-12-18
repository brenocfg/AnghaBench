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

/* Variables and functions */
 int /*<<< orphan*/  blit_line ; 
 int /*<<< orphan*/  blit_line_extended ; 
 int /*<<< orphan*/  blit_line_extended_shadow ; 
 int /*<<< orphan*/  blit_line_regular ; 
 int /*<<< orphan*/  blit_line_regular_shadow ; 
 int /*<<< orphan*/  blit_symbol ; 
 int /*<<< orphan*/  blit_symbol_regular ; 
 int /*<<< orphan*/  blit_symbol_shadow ; 

__attribute__((used)) static void rgui_set_blit_functions(bool draw_shadow, bool extended_ascii)
{
   if (draw_shadow)
   {
      if (extended_ascii)
         blit_line = blit_line_extended_shadow;
      else
         blit_line = blit_line_regular_shadow;
      
      blit_symbol = blit_symbol_shadow;
   }
   else
   {
      if (extended_ascii)
         blit_line = blit_line_extended;
      else
         blit_line = blit_line_regular;
      
      blit_symbol = blit_symbol_regular;
   }
}