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
typedef  int /*<<< orphan*/  materialui_theme_t ;
typedef  enum materialui_color_theme { ____Placeholder_materialui_color_theme } materialui_color_theme ;

/* Variables and functions */
#define  MATERIALUI_THEME_BLUE 148 
#define  MATERIALUI_THEME_BLUE_GREY 147 
#define  MATERIALUI_THEME_CUTIE_BLUE 146 
#define  MATERIALUI_THEME_CUTIE_CYAN 145 
#define  MATERIALUI_THEME_CUTIE_GREEN 144 
#define  MATERIALUI_THEME_CUTIE_ORANGE 143 
#define  MATERIALUI_THEME_CUTIE_PINK 142 
#define  MATERIALUI_THEME_CUTIE_PURPLE 141 
#define  MATERIALUI_THEME_CUTIE_RED 140 
#define  MATERIALUI_THEME_DARK_BLUE 139 
#define  MATERIALUI_THEME_GREEN 138 
#define  MATERIALUI_THEME_GRUVBOX_DARK 137 
#define  MATERIALUI_THEME_MATERIALUI 136 
#define  MATERIALUI_THEME_MATERIALUI_DARK 135 
#define  MATERIALUI_THEME_NORD 134 
#define  MATERIALUI_THEME_NVIDIA_SHIELD 133 
#define  MATERIALUI_THEME_OZONE_DARK 132 
#define  MATERIALUI_THEME_RED 131 
#define  MATERIALUI_THEME_SOLARIZED_DARK 130 
#define  MATERIALUI_THEME_VIRTUAL_BOY 129 
#define  MATERIALUI_THEME_YELLOW 128 
 int /*<<< orphan*/  const materialui_theme_blue ; 
 int /*<<< orphan*/  const materialui_theme_blue_grey ; 
 int /*<<< orphan*/  const materialui_theme_cutie_blue ; 
 int /*<<< orphan*/  const materialui_theme_cutie_cyan ; 
 int /*<<< orphan*/  const materialui_theme_cutie_green ; 
 int /*<<< orphan*/  const materialui_theme_cutie_orange ; 
 int /*<<< orphan*/  const materialui_theme_cutie_pink ; 
 int /*<<< orphan*/  const materialui_theme_cutie_purple ; 
 int /*<<< orphan*/  const materialui_theme_cutie_red ; 
 int /*<<< orphan*/  const materialui_theme_dark_blue ; 
 int /*<<< orphan*/  const materialui_theme_green ; 
 int /*<<< orphan*/  const materialui_theme_gruvbox_dark ; 
 int /*<<< orphan*/  const materialui_theme_materialui ; 
 int /*<<< orphan*/  const materialui_theme_materialui_dark ; 
 int /*<<< orphan*/  const materialui_theme_nord ; 
 int /*<<< orphan*/  const materialui_theme_nvidia_shield ; 
 int /*<<< orphan*/  const materialui_theme_ozone_dark ; 
 int /*<<< orphan*/  const materialui_theme_red ; 
 int /*<<< orphan*/  const materialui_theme_solarized_dark ; 
 int /*<<< orphan*/  const materialui_theme_virtual_boy ; 
 int /*<<< orphan*/  const materialui_theme_yellow ; 

__attribute__((used)) static const materialui_theme_t *materialui_get_theme(enum materialui_color_theme color_theme)
{
   switch (color_theme)
   {
      case MATERIALUI_THEME_BLUE:
         return &materialui_theme_blue;
      case MATERIALUI_THEME_BLUE_GREY:
         return &materialui_theme_blue_grey;
      case MATERIALUI_THEME_DARK_BLUE:
         return &materialui_theme_dark_blue;
      case MATERIALUI_THEME_GREEN:
         return &materialui_theme_green;
      case MATERIALUI_THEME_RED:
         return &materialui_theme_red;
      case MATERIALUI_THEME_YELLOW:
         return &materialui_theme_yellow;
      case MATERIALUI_THEME_NVIDIA_SHIELD:
         return &materialui_theme_nvidia_shield;
      case MATERIALUI_THEME_MATERIALUI:
         return &materialui_theme_materialui;
      case MATERIALUI_THEME_MATERIALUI_DARK:
         return &materialui_theme_materialui_dark;
      case MATERIALUI_THEME_OZONE_DARK:
         return &materialui_theme_ozone_dark;
      case MATERIALUI_THEME_NORD:
         return &materialui_theme_nord;
      case MATERIALUI_THEME_GRUVBOX_DARK:
         return &materialui_theme_gruvbox_dark;
      case MATERIALUI_THEME_SOLARIZED_DARK:
         return &materialui_theme_solarized_dark;
      case MATERIALUI_THEME_CUTIE_BLUE:
         return &materialui_theme_cutie_blue;
      case MATERIALUI_THEME_CUTIE_CYAN:
         return &materialui_theme_cutie_cyan;
      case MATERIALUI_THEME_CUTIE_GREEN:
         return &materialui_theme_cutie_green;
      case MATERIALUI_THEME_CUTIE_ORANGE:
         return &materialui_theme_cutie_orange;
      case MATERIALUI_THEME_CUTIE_PINK:
         return &materialui_theme_cutie_pink;
      case MATERIALUI_THEME_CUTIE_PURPLE:
         return &materialui_theme_cutie_purple;
      case MATERIALUI_THEME_CUTIE_RED:
         return &materialui_theme_cutie_red;
      case MATERIALUI_THEME_VIRTUAL_BOY:
         return &materialui_theme_virtual_boy;
      default:
         break;
   }

   return &materialui_theme_blue;
}