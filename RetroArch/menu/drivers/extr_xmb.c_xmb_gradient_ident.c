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
struct TYPE_3__ {int xmb_color_theme; } ;
typedef  TYPE_1__ video_frame_info_t ;

/* Variables and functions */
#define  XMB_THEME_APPLE_GREEN 139 
#define  XMB_THEME_DARK 138 
#define  XMB_THEME_DARK_PURPLE 137 
#define  XMB_THEME_ELECTRIC_BLUE 136 
#define  XMB_THEME_GOLDEN 135 
#define  XMB_THEME_LEGACY_RED 134 
#define  XMB_THEME_LIGHT 133 
#define  XMB_THEME_MIDNIGHT_BLUE 132 
#define  XMB_THEME_MORNING_BLUE 131 
#define  XMB_THEME_SUNBEAM 130 
#define  XMB_THEME_UNDERSEA 129 
#define  XMB_THEME_VOLCANIC_RED 128 
 float* gradient_apple_green ; 
 float* gradient_dark ; 
 float* gradient_dark_purple ; 
 float* gradient_electric_blue ; 
 float* gradient_golden ; 
 float* gradient_legacy_red ; 
 float* gradient_light ; 
 float* gradient_midnight_blue ; 
 float* gradient_morning_blue ; 
 float* gradient_sunbeam ; 
 float* gradient_undersea ; 
 float* gradient_volcanic_red ; 

__attribute__((used)) static float *xmb_gradient_ident(video_frame_info_t *video_info)
{
   switch (video_info->xmb_color_theme)
   {
      case XMB_THEME_DARK_PURPLE:
         return &gradient_dark_purple[0];
      case XMB_THEME_MIDNIGHT_BLUE:
         return &gradient_midnight_blue[0];
      case XMB_THEME_GOLDEN:
         return &gradient_golden[0];
      case XMB_THEME_ELECTRIC_BLUE:
         return &gradient_electric_blue[0];
      case XMB_THEME_APPLE_GREEN:
         return &gradient_apple_green[0];
      case XMB_THEME_UNDERSEA:
         return &gradient_undersea[0];
      case XMB_THEME_VOLCANIC_RED:
         return &gradient_volcanic_red[0];
      case XMB_THEME_DARK:
         return &gradient_dark[0];
      case XMB_THEME_LIGHT:
         return &gradient_light[0];
      case XMB_THEME_MORNING_BLUE:
         return &gradient_morning_blue[0];
      case XMB_THEME_SUNBEAM:
         return &gradient_sunbeam[0];         
      case XMB_THEME_LEGACY_RED:
      default:
         break;
   }

   return &gradient_legacy_red[0];
}