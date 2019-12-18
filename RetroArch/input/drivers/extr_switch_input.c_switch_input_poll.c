#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_10__ {int /*<<< orphan*/  py; int /*<<< orphan*/  px; } ;
typedef  TYPE_2__ touchPosition ;
struct TYPE_11__ {int* previous_touch_state; int* touch_state; int* keyboard_state; int mouse_previous_report; int mouse_button_left; int mouse_button_right; int mouse_button_middle; scalar_t__ mouse_x_delta; scalar_t__ mouse_y_delta; scalar_t__ mouse_x; scalar_t__ mouse_y; int /*<<< orphan*/  mouse_wheel; int /*<<< orphan*/ * touch_y_screen; int /*<<< orphan*/ * touch_x_screen; int /*<<< orphan*/ * touch_y_viewport; int /*<<< orphan*/ * touch_x_viewport; int /*<<< orphan*/ * touch_y; int /*<<< orphan*/ * touch_x; int /*<<< orphan*/ * touch_previous_y; int /*<<< orphan*/ * touch_previous_x; TYPE_1__* joypad; } ;
typedef  TYPE_3__ switch_input_t ;
struct video_viewport {scalar_t__ full_height; scalar_t__ full_width; scalar_t__ height; scalar_t__ width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_13__ {int sym; } ;
struct TYPE_12__ {scalar_t__ velocityX; scalar_t__ velocityY; int /*<<< orphan*/  scrollVelocityY; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* poll ) () ;} ;
typedef  TYPE_4__ MousePosition ;

/* Variables and functions */
 int KBD_LEFTALT ; 
 int KBD_LEFTCTRL ; 
 int KBD_LEFTSHIFT ; 
 int KBD_RIGHTALT ; 
 int KBD_RIGHTCTRL ; 
 int KBD_RIGHTSHIFT ; 
 int MOUSE_LEFT ; 
 scalar_t__ MOUSE_MAX_X ; 
 scalar_t__ MOUSE_MAX_Y ; 
 int MOUSE_MIDDLE ; 
 int MOUSE_RIGHT ; 
 unsigned int MULTITOUCH_LIMIT ; 
 int /*<<< orphan*/  RETROKMOD_ALT ; 
 int /*<<< orphan*/  RETROKMOD_CTRL ; 
 int /*<<< orphan*/  RETROKMOD_SHIFT ; 
 int /*<<< orphan*/  RETRO_DEVICE_KEYBOARD ; 
 unsigned int SWITCH_NUM_SCANCODES ; 
 int /*<<< orphan*/  handle_touch_mouse (TYPE_3__*) ; 
 scalar_t__ hidKeyboardHeld (int) ; 
 int hidMouseButtonsHeld () ; 
 int /*<<< orphan*/  hidMouseRead (TYPE_4__*) ; 
 unsigned int hidTouchCount () ; 
 int /*<<< orphan*/  hidTouchRead (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  input_keyboard_event (int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int input_keymaps_translate_keysym_to_rk (int) ; 
 TYPE_5__* rarch_key_map_switch ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  video_driver_translate_coord_viewport_wrap (struct video_viewport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void switch_input_poll(void *data)
{
   switch_input_t *sw = (switch_input_t*) data;
#ifdef HAVE_LIBNX
   uint32_t touch_count;
   unsigned int i = 0;
   int keySym = 0;
   unsigned keyCode = 0;
   uint16_t mod = 0;
   MousePosition mouse_pos;
   uint64_t mouse_current_report = 0;
#endif

   if (sw->joypad)
      sw->joypad->poll();

#ifdef HAVE_LIBNX
   touch_count = hidTouchCount();
   for (i = 0; i < MULTITOUCH_LIMIT; i++)
   {
      sw->previous_touch_state[i] = sw->touch_state[i];
      sw->touch_state[i] = touch_count > i;

      if (sw->touch_state[i])
      {
         struct video_viewport vp;
         touchPosition touch_position;
         hidTouchRead(&touch_position, i);

         sw->touch_previous_x[i] = sw->touch_x[i];
         sw->touch_previous_y[i] = sw->touch_y[i];
         sw->touch_x[i] = touch_position.px;
         sw->touch_y[i] = touch_position.py;

         /* convert from event coordinates to core and screen coordinates */
         vp.x                        = 0;
         vp.y                        = 0;
         vp.width                    = 0;
         vp.height                   = 0;
         vp.full_width               = 0;
         vp.full_height              = 0;

         video_driver_translate_coord_viewport_wrap(
            &vp,
            touch_position.px,
            touch_position.py,
            &sw->touch_x_viewport[i],
            &sw->touch_y_viewport[i],
            &sw->touch_x_screen[i],
            &sw->touch_y_screen[i]);
      }
   }

   mod = 0;
   if (hidKeyboardHeld(KBD_LEFTALT) || hidKeyboardHeld(KBD_RIGHTALT))
      mod |= RETROKMOD_ALT;
   if (hidKeyboardHeld(KBD_LEFTCTRL) || hidKeyboardHeld(KBD_RIGHTCTRL))
      mod |= RETROKMOD_CTRL;
   if (hidKeyboardHeld(KBD_LEFTSHIFT) || hidKeyboardHeld(KBD_RIGHTSHIFT))
      mod |= RETROKMOD_SHIFT;

   for (i = 0; i < SWITCH_NUM_SCANCODES; i++)
   {
      keySym = rarch_key_map_switch[i].sym;
      keyCode = input_keymaps_translate_keysym_to_rk(keySym);

      if (hidKeyboardHeld(keySym) && !(sw->keyboard_state[keySym]))
      {
         sw->keyboard_state[keySym] = true;
         input_keyboard_event(true, keyCode, 0, mod, RETRO_DEVICE_KEYBOARD);
      }
      else if (!hidKeyboardHeld(keySym) && sw->keyboard_state[keySym])
      {
         sw->keyboard_state[keySym] = false;
         input_keyboard_event(false, keyCode, 0, mod, RETRO_DEVICE_KEYBOARD);
      }
   }

   /* update physical mouse buttons only when they change
    * this allows the physical mouse and touch mouse to coexist */
   mouse_current_report = hidMouseButtonsHeld();
   if ((mouse_current_report & MOUSE_LEFT) != (sw->mouse_previous_report & MOUSE_LEFT))
   {
      if (mouse_current_report & MOUSE_LEFT)
         sw->mouse_button_left = true;
      else
         sw->mouse_button_left = false;
   }

   if ((mouse_current_report & MOUSE_RIGHT) != (sw->mouse_previous_report & MOUSE_RIGHT))
   {
      if (mouse_current_report & MOUSE_RIGHT)
         sw->mouse_button_right = true;
      else
         sw->mouse_button_right = false;
   }

   if ((mouse_current_report & MOUSE_MIDDLE) != (sw->mouse_previous_report & MOUSE_MIDDLE))
   {
      if (mouse_current_report & MOUSE_MIDDLE)
         sw->mouse_button_middle = true;
      else
         sw->mouse_button_middle = false;
   }
   sw->mouse_previous_report = mouse_current_report;

   /* physical mouse position */
   hidMouseRead(&mouse_pos);

   sw->mouse_x_delta = mouse_pos.velocityX;
   sw->mouse_y_delta = mouse_pos.velocityY;

   sw->mouse_x += sw->mouse_x_delta;
   sw->mouse_y += sw->mouse_y_delta;

   /* touch mouse events
    * handle_touch_mouse will update sw->mouse_* variables
    * depending on touch input gestures
    * see first comment in process_touch_mouse_event() for a list of
    * supported touch gestures */
   handle_touch_mouse(sw);

   if (sw->mouse_x < 0)
      sw->mouse_x = 0;
   else if (sw->mouse_x > MOUSE_MAX_X)
      sw->mouse_x = MOUSE_MAX_X;

   if (sw->mouse_y < 0) 
      sw->mouse_y = 0;
   else if (sw->mouse_y > MOUSE_MAX_Y)
      sw->mouse_y = MOUSE_MAX_Y;

   sw->mouse_wheel = mouse_pos.scrollVelocityY;
#endif
}