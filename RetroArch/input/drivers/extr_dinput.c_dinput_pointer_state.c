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
struct video_viewport {scalar_t__ full_height; scalar_t__ full_width; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct pointer_status {int pointer_x; int pointer_y; struct pointer_status* next; } ;
struct TYPE_2__ {struct pointer_status* next; } ;
struct dinput_input {int mouse_x; int mouse_y; int mouse_l; TYPE_1__ pointer_head; } ;
typedef  int int16_t ;

/* Variables and functions */
#define  RETRO_DEVICE_ID_POINTER_PRESSED 130 
#define  RETRO_DEVICE_ID_POINTER_X 129 
#define  RETRO_DEVICE_ID_POINTER_Y 128 
 int /*<<< orphan*/  video_driver_translate_coord_viewport_wrap (struct video_viewport*,int,int,int*,int*,int*,int*) ; 

__attribute__((used)) static int16_t dinput_pointer_state(struct dinput_input *di,
      unsigned idx, unsigned id, bool screen)
{
   struct video_viewport vp;
   bool pointer_down           = false;
   bool inside                 = false;
   int x                       = 0;
   int y                       = 0;
   int16_t res_x               = 0;
   int16_t res_y               = 0;
   int16_t res_screen_x        = 0;
   int16_t res_screen_y        = 0;
   unsigned num                = 0;
   struct pointer_status *
      check_pos                = di->pointer_head.next;

   vp.x                        = 0;
   vp.y                        = 0;
   vp.width                    = 0;
   vp.height                   = 0;
   vp.full_width               = 0;
   vp.full_height              = 0;

   while (check_pos && num < idx)
   {
      num++;
      check_pos    = check_pos->next;
   }
   if (!check_pos && idx > 0) /* idx = 0 has mouse fallback. */
      return 0;

   x               = di->mouse_x;
   y               = di->mouse_y;
   pointer_down    = di->mouse_l;

   if (check_pos)
   {
      x            = check_pos->pointer_x;
      y            = check_pos->pointer_y;
      pointer_down = true;
   }

   if (!(video_driver_translate_coord_viewport_wrap(&vp, x, y,
         &res_x, &res_y, &res_screen_x, &res_screen_y)))
      return 0;

   if (screen)
   {
      res_x        = res_screen_x;
      res_y        = res_screen_y;
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
         return pointer_down;
      default:
         break;
   }

   return 0;
}