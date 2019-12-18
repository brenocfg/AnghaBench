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
 int /*<<< orphan*/ * caca_display ; 
 int /*<<< orphan*/ * caca_dither ; 
 int /*<<< orphan*/  caca_free_display (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  caca_free_dither (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * caca_menu_frame ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void caca_gfx_free(void *data)
{
   (void)data;

   if (caca_display)
   {
      caca_free_display(caca_display);
      caca_display = NULL;
   }

   if (caca_dither)
   {
      caca_free_dither(caca_dither);
      caca_dither = NULL;
   }

   if (caca_menu_frame)
   {
      free(caca_menu_frame);
      caca_menu_frame = NULL;
   }
}