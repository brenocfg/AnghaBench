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
struct TYPE_8__ {int x; int dlt_x; int y; int dlt_y; int /*<<< orphan*/  btn_b5; int /*<<< orphan*/  btn_b4; int /*<<< orphan*/  btn_m; int /*<<< orphan*/  whl_d; int /*<<< orphan*/  whl_u; int /*<<< orphan*/  btn_r; int /*<<< orphan*/  btn_l; } ;
typedef  TYPE_2__ winraw_mouse_t ;
struct TYPE_9__ {TYPE_2__* mice; } ;
typedef  TYPE_3__ winraw_input_t ;
struct TYPE_7__ {unsigned int* input_mouse_index; } ;
struct TYPE_10__ {TYPE_1__ uints; } ;
typedef  TYPE_4__ settings_t ;
typedef  int int16_t ;

/* Variables and functions */
 unsigned int MAX_USERS ; 
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_4 136 
#define  RETRO_DEVICE_ID_MOUSE_BUTTON_5 135 
#define  RETRO_DEVICE_ID_MOUSE_LEFT 134 
#define  RETRO_DEVICE_ID_MOUSE_MIDDLE 133 
#define  RETRO_DEVICE_ID_MOUSE_RIGHT 132 
#define  RETRO_DEVICE_ID_MOUSE_WHEELDOWN 131 
#define  RETRO_DEVICE_ID_MOUSE_WHEELUP 130 
#define  RETRO_DEVICE_ID_MOUSE_X 129 
#define  RETRO_DEVICE_ID_MOUSE_Y 128 
 TYPE_4__* config_get_ptr () ; 
 unsigned int g_mouse_cnt ; 

__attribute__((used)) static int16_t winraw_mouse_state(winraw_input_t *wr,
      unsigned port, bool abs, unsigned id)
{
   unsigned i;
   settings_t *settings  = config_get_ptr();
   winraw_mouse_t *mouse = NULL;

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

   switch (id)
   {
      case RETRO_DEVICE_ID_MOUSE_X:
         return abs ? mouse->x : mouse->dlt_x;
      case RETRO_DEVICE_ID_MOUSE_Y:
         return abs ? mouse->y : mouse->dlt_y;
      case RETRO_DEVICE_ID_MOUSE_LEFT:
         return mouse->btn_l ? 1 : 0;
      case RETRO_DEVICE_ID_MOUSE_RIGHT:
         return mouse->btn_r ? 1 : 0;
      case RETRO_DEVICE_ID_MOUSE_WHEELUP:
         return mouse->whl_u ? 1 : 0;
      case RETRO_DEVICE_ID_MOUSE_WHEELDOWN:
         return mouse->whl_d ? 1 : 0;
      case RETRO_DEVICE_ID_MOUSE_MIDDLE:
         return mouse->btn_m ? 1 : 0;
      case RETRO_DEVICE_ID_MOUSE_BUTTON_4:
         return mouse->btn_b4 ? 1 : 0;
      case RETRO_DEVICE_ID_MOUSE_BUTTON_5:
         return mouse->btn_b5 ? 1 : 0;
   }

   return 0;
}