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
typedef  int /*<<< orphan*/  fontpath ;
typedef  int /*<<< orphan*/  font_data_t ;
typedef  enum application_special_type { ____Placeholder_application_special_type } application_special_type ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  fill_pathname_application_special (char*,int,int) ; 
 int /*<<< orphan*/  menu_disp ; 
 int /*<<< orphan*/ * menu_display_font_file (char*,float,int) ; 

font_data_t *menu_display_font(
      enum application_special_type type,
      float menu_font_size,
      bool is_threaded)
{
   char fontpath[PATH_MAX_LENGTH];

   if (!menu_disp)
      return NULL;

   fontpath[0] = '\0';

   fill_pathname_application_special(
         fontpath, sizeof(fontpath), type);

   return menu_display_font_file(fontpath, menu_font_size, is_threaded);
}