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
typedef  int /*<<< orphan*/  font_data_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* font_init_first ) (void**,int /*<<< orphan*/ ,char*,float,int) ;} ;

/* Variables and functions */
 TYPE_1__* menu_disp ; 
 int /*<<< orphan*/  stub1 (void**,int /*<<< orphan*/ ,char*,float,int) ; 
 int /*<<< orphan*/  video_driver_get_ptr (int) ; 

font_data_t *menu_display_font_file(char* fontpath, float menu_font_size, bool is_threaded)
{
   font_data_t *font_data = NULL;

   if (!menu_disp)
      return NULL;

   if (!menu_disp->font_init_first((void**)&font_data,
            video_driver_get_ptr(false),
            fontpath, menu_font_size, is_threaded))
      return NULL;

   return font_data;
}