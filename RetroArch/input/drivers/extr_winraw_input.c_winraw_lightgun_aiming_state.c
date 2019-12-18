#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ winraw_mouse_t ;
struct TYPE_9__ {TYPE_2__* mice; } ;
typedef  TYPE_3__ winraw_input_t ;
struct video_viewport {scalar_t__ full_height; scalar_t__ full_width; scalar_t__ height; scalar_t__ width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_7__ {unsigned int* input_mouse_index; } ;
struct TYPE_10__ {TYPE_1__ uints; } ;
typedef  TYPE_4__ settings_t ;
typedef  int const int16_t ;

/* Variables and functions */
 unsigned int MAX_USERS ; 
#define  RETRO_DEVICE_ID_LIGHTGUN_IS_OFFSCREEN 130 
#define  RETRO_DEVICE_ID_LIGHTGUN_SCREEN_X 129 
#define  RETRO_DEVICE_ID_LIGHTGUN_SCREEN_Y 128 
 TYPE_4__* config_get_ptr () ; 
 unsigned int g_mouse_cnt ; 
 int /*<<< orphan*/  video_driver_translate_coord_viewport_wrap (struct video_viewport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int const*,int const*,int const*) ; 

__attribute__((used)) static int16_t winraw_lightgun_aiming_state(winraw_input_t *wr,
      unsigned port, unsigned id)
{
   const int edge_detect = 32700;
   struct video_viewport vp;
   bool inside = false;
   unsigned i;
   settings_t *settings  = config_get_ptr();
   winraw_mouse_t *mouse = NULL;
   int16_t res_x = 0;
   int16_t res_y = 0;
   int16_t res_screen_x = 0;
   int16_t res_screen_y = 0;

   if (port >= MAX_USERS)
      return 0;

   for (i = 0; i < g_mouse_cnt; ++i)
   {
      if (i == settings->uints.input_mouse_index[port])
      {
         mouse = &wr->mice[i];
         break;
      }
   }

   if (!mouse)
      return 0;

   vp.x = 0;
   vp.y = 0;
   vp.width = 0;
   vp.height = 0;
   vp.full_width = 0;
   vp.full_height = 0;

   if ( !( video_driver_translate_coord_viewport_wrap(
               &vp, mouse->x, mouse->y, &res_x, &res_y, &res_screen_x, &res_screen_y ) ) )
      return 0;

   inside = (res_x >= -edge_detect) && (res_y >= -edge_detect) && (res_x <= edge_detect) && (res_y <= edge_detect);

   switch ( id )
   {
      case RETRO_DEVICE_ID_LIGHTGUN_SCREEN_X:
         return inside ? res_x : 0;
      case RETRO_DEVICE_ID_LIGHTGUN_SCREEN_Y:
         return inside ? res_y : 0;
      case RETRO_DEVICE_ID_LIGHTGUN_IS_OFFSCREEN:
         return !inside;
      default:
         break;
   }

   return 0;
}