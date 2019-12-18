#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct dinput_input {TYPE_1__* joypad; scalar_t__ mouse_y; scalar_t__ mouse_x; scalar_t__ mouse_b5; scalar_t__ mouse_b4; scalar_t__ mouse_m; scalar_t__ mouse_r; scalar_t__ mouse_l; int /*<<< orphan*/  mouse_rel_y; int /*<<< orphan*/  mouse_rel_x; scalar_t__ mouse; TYPE_3__* state; scalar_t__ keyboard; } ;
typedef  int /*<<< orphan*/  mouse_state ;
struct TYPE_10__ {scalar_t__* rgbButtons; int /*<<< orphan*/  lY; int /*<<< orphan*/  lX; } ;
struct TYPE_9__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* poll ) () ;} ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_3__ DIMOUSESTATE2 ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCursorPos (TYPE_2__*) ; 
 int /*<<< orphan*/  IDirectInputDevice8_Acquire (scalar_t__) ; 
 int /*<<< orphan*/  IDirectInputDevice8_GetDeviceState (scalar_t__,int,TYPE_3__*) ; 
 int /*<<< orphan*/  ScreenToClient (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ doubleclick_on_titlebar_pressed () ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  unset_doubleclick_on_titlebar () ; 
 scalar_t__ video_driver_window_get () ; 

__attribute__((used)) static void dinput_poll(void *data)
{
   struct dinput_input *di = (struct dinput_input*)data;

   if (!di)
      return;

   memset(di->state, 0, sizeof(di->state));
   if (di->keyboard)
   {
      if (FAILED(IDirectInputDevice8_GetDeviceState(
                  di->keyboard, sizeof(di->state), di->state)))
      {
         IDirectInputDevice8_Acquire(di->keyboard);
         if (FAILED(IDirectInputDevice8_GetDeviceState(
                     di->keyboard, sizeof(di->state), di->state)))
            memset(di->state, 0, sizeof(di->state));
      }
   }

   if (di->mouse)
   {
      POINT point;
      DIMOUSESTATE2 mouse_state;
      
      point.x = 0;
      point.y = 0;

      memset(&mouse_state, 0, sizeof(mouse_state));

      if (FAILED(IDirectInputDevice8_GetDeviceState(
                  di->mouse, sizeof(mouse_state), &mouse_state)))
      {
         IDirectInputDevice8_Acquire(di->mouse);
         if (FAILED(IDirectInputDevice8_GetDeviceState(
                     di->mouse, sizeof(mouse_state), &mouse_state)))
            memset(&mouse_state, 0, sizeof(mouse_state));
      }

      di->mouse_rel_x = mouse_state.lX;
      di->mouse_rel_y = mouse_state.lY;

      if (!mouse_state.rgbButtons[0])
         unset_doubleclick_on_titlebar();
      if (doubleclick_on_titlebar_pressed())
         di->mouse_l  = 0;
      else
         di->mouse_l  = mouse_state.rgbButtons[0];
      di->mouse_r     = mouse_state.rgbButtons[1];
      di->mouse_m     = mouse_state.rgbButtons[2];
      di->mouse_b4    = mouse_state.rgbButtons[3];
      di->mouse_b5    = mouse_state.rgbButtons[4];

      /* No simple way to get absolute coordinates
       * for RETRO_DEVICE_POINTER. Just use Win32 APIs. */
      GetCursorPos(&point);
      ScreenToClient((HWND)video_driver_window_get(), &point);
      di->mouse_x = point.x;
      di->mouse_y = point.y;
   }

   if (di->joypad)
      di->joypad->poll();
}