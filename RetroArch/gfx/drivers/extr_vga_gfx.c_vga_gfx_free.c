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
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vga_frame ; 
 int /*<<< orphan*/ * vga_menu_frame ; 
 int /*<<< orphan*/  vga_return_to_text_mode () ; 

__attribute__((used)) static void vga_gfx_free(void *data)
{
   (void)data;

   if (vga_frame)
   {
      free(vga_frame);
      vga_frame = NULL;
   }

   if (vga_menu_frame)
   {
      free(vga_menu_frame);
      vga_menu_frame = NULL;
   }

   vga_return_to_text_mode();
}