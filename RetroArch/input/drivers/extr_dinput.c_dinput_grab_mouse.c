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
struct dinput_input {int /*<<< orphan*/  mouse; } ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int DISCL_EXCLUSIVE ; 
 int DISCL_FOREGROUND ; 
 int DISCL_NONEXCLUSIVE ; 
 int /*<<< orphan*/  IDirectInputDevice8_Acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectInputDevice8_SetCooperativeLevel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirectInputDevice8_Unacquire (int /*<<< orphan*/ ) ; 
 scalar_t__ video_driver_window_get () ; 

__attribute__((used)) static void dinput_grab_mouse(void *data, bool state)
{
   struct dinput_input *di = (struct dinput_input*)data;

   IDirectInputDevice8_Unacquire(di->mouse);
   IDirectInputDevice8_SetCooperativeLevel(di->mouse,
      (HWND)video_driver_window_get(),
      state ?
      (DISCL_EXCLUSIVE | DISCL_FOREGROUND) :
      (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND));
   IDirectInputDevice8_Acquire(di->mouse);
}