#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int menu_xmb_theme; } ;
struct TYPE_5__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
#define  XMB_ICON_THEME_AUTOMATIC 139 
#define  XMB_ICON_THEME_AUTOMATIC_INVERTED 138 
#define  XMB_ICON_THEME_CUSTOM 137 
#define  XMB_ICON_THEME_DOTART 136 
#define  XMB_ICON_THEME_FLATUI 135 
#define  XMB_ICON_THEME_MONOCHROME 134 
#define  XMB_ICON_THEME_MONOCHROME_INVERTED 133 
#define  XMB_ICON_THEME_NEOACTIVE 132 
#define  XMB_ICON_THEME_PIXEL 131 
#define  XMB_ICON_THEME_RETROACTIVE 130 
#define  XMB_ICON_THEME_RETROSYSTEM 129 
#define  XMB_ICON_THEME_SYSTEMATIC 128 
 TYPE_2__* config_get_ptr () ; 

const char* xmb_theme_ident(void)
{
   settings_t *settings = config_get_ptr();
   switch (settings->uints.menu_xmb_theme)
   {
      case XMB_ICON_THEME_FLATUI:
         return "flatui";
      case XMB_ICON_THEME_RETROACTIVE:
         return "retroactive";
      case XMB_ICON_THEME_RETROSYSTEM:
         return "retrosystem";
      case XMB_ICON_THEME_PIXEL:
         return "pixel";
      case XMB_ICON_THEME_NEOACTIVE:
         return "neoactive";
      case XMB_ICON_THEME_SYSTEMATIC:
         return "systematic";
      case XMB_ICON_THEME_DOTART:
         return "dot-art";
      case XMB_ICON_THEME_CUSTOM:
         return "custom";
      case XMB_ICON_THEME_MONOCHROME_INVERTED:
         return "monochrome";
      case XMB_ICON_THEME_AUTOMATIC:
         return "automatic";
      case XMB_ICON_THEME_AUTOMATIC_INVERTED:
         return "automatic";
      case XMB_ICON_THEME_MONOCHROME:
      default:
         break;
   }
   return "monochrome";
}