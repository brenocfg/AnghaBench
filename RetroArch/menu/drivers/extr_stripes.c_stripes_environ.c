#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mouse_show; } ;
typedef  TYPE_1__ stripes_handle_t ;
typedef  enum menu_environ_cb { ____Placeholder_menu_environ_cb } menu_environ_cb ;

/* Variables and functions */
#define  MENU_ENVIRON_DISABLE_MOUSE_CURSOR 130 
#define  MENU_ENVIRON_ENABLE_MOUSE_CURSOR 129 
#define  MENU_ENVIRON_RESET_HORIZONTAL_LIST 128 
 int /*<<< orphan*/  stripes_refresh_horizontal_list (TYPE_1__*) ; 

__attribute__((used)) static int stripes_environ(enum menu_environ_cb type, void *data, void *userdata)
{
   stripes_handle_t *stripes        = (stripes_handle_t*)userdata;

   switch (type)
   {
      case MENU_ENVIRON_ENABLE_MOUSE_CURSOR:
         if (!stripes)
            return -1;
         stripes->mouse_show = true;
         break;
      case MENU_ENVIRON_DISABLE_MOUSE_CURSOR:
         if (!stripes)
            return -1;
         stripes->mouse_show = false;
         break;
      case MENU_ENVIRON_RESET_HORIZONTAL_LIST:
         if (!stripes)
            return -1;

         stripes_refresh_horizontal_list(stripes);
         break;
      default:
         return -1;
   }

   return 0;
}