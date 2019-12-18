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
struct TYPE_3__ {int mouse_l; int /*<<< orphan*/  mouse_y; int /*<<< orphan*/  mouse_x; } ;
typedef  TYPE_1__ x11_input_t ;
struct video_viewport {scalar_t__ full_height; scalar_t__ full_width; scalar_t__ height; scalar_t__ width; scalar_t__ y; scalar_t__ x; } ;
typedef  int int16_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_POINTER_PRESSED 130 
#define  RETRO_DEVICE_ID_POINTER_X 129 
#define  RETRO_DEVICE_ID_POINTER_Y 128 
 int /*<<< orphan*/  video_driver_translate_coord_viewport_wrap (struct video_viewport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*,int*) ; 

__attribute__((used)) static int16_t x_pointer_state(x11_input_t *x11,
      unsigned idx, unsigned id, bool screen)
{
   struct video_viewport vp;
   bool inside                 = false;
   int16_t res_x               = 0;
   int16_t res_y               = 0;
   int16_t res_screen_x        = 0;
   int16_t res_screen_y        = 0;

   vp.x                        = 0;
   vp.y                        = 0;
   vp.width                    = 0;
   vp.height                   = 0;
   vp.full_width               = 0;
   vp.full_height              = 0;

   if (!(video_driver_translate_coord_viewport_wrap(&vp, x11->mouse_x, x11->mouse_y,
         &res_x, &res_y, &res_screen_x, &res_screen_y)))
      return 0;

   if (screen)
   {
      res_x = res_screen_x;
      res_y = res_screen_y;
   }

   inside = (res_x >= -0x7fff) && (res_y >= -0x7fff);

   if (!inside)
      return 0;

   switch (id)
   {
      case RETRO_DEVICE_ID_POINTER_X:
         return res_x;
      case RETRO_DEVICE_ID_POINTER_Y:
         return res_y;
      case RETRO_DEVICE_ID_POINTER_PRESSED:
         return x11->mouse_l;
   }

   return 0;
}