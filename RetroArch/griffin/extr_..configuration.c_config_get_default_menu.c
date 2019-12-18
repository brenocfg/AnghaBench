#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum menu_driver_enum { ____Placeholder_menu_driver_enum } menu_driver_enum ;
struct TYPE_3__ {char const* menu; } ;
struct TYPE_4__ {TYPE_1__ settings; } ;

/* Variables and functions */
 int MENU_DEFAULT_DRIVER ; 
#define  MENU_MATERIALUI 134 
#define  MENU_NULL 133 
#define  MENU_OZONE 132 
#define  MENU_RGUI 131 
#define  MENU_STRIPES 130 
#define  MENU_XMB 129 
#define  MENU_XUI 128 
 TYPE_2__ g_defaults ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 

const char *config_get_default_menu(void)
{
#ifdef HAVE_MENU
   enum menu_driver_enum default_driver = MENU_DEFAULT_DRIVER;

   if (!string_is_empty(g_defaults.settings.menu))
      return g_defaults.settings.menu;

   switch (default_driver)
   {
      case MENU_RGUI:
         return "rgui";
      case MENU_XUI:
         return "xui";
      case MENU_OZONE:
         return "ozone";
      case MENU_MATERIALUI:
         return "glui";
      case MENU_XMB:
         return "xmb";
      case MENU_STRIPES:
         return "stripes";
      case MENU_NULL:
         break;
   }
#endif

   return "null";
}