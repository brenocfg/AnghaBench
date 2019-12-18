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
typedef  int /*<<< orphan*/  sixel_t ;

/* Variables and functions */
 int /*<<< orphan*/  font_driver_free_osd () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * sixel_menu_frame ; 
 int /*<<< orphan*/ * sixel_temp_buf ; 

__attribute__((used)) static void sixel_gfx_free(void *data)
{
   sixel_t *sixel = (sixel_t*)data;

   printf("\033\\");

   if (sixel_menu_frame)
   {
      free(sixel_menu_frame);
      sixel_menu_frame = NULL;
   }

   if (sixel_temp_buf)
   {
      free(sixel_temp_buf);
      sixel_temp_buf = NULL;
   }

   font_driver_free_osd();

   if (sixel)
      free(sixel);
}