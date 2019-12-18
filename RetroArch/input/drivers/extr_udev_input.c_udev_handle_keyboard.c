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
struct TYPE_2__ {int /*<<< orphan*/  xkb_handling; } ;
typedef  TYPE_1__ udev_input_t ;
typedef  int /*<<< orphan*/  udev_input_device_t ;
struct input_event {int type; int /*<<< orphan*/  value; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_CLEAR (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  BIT_SET (int /*<<< orphan*/ ,unsigned int) ; 
#define  EV_KEY 128 
 int /*<<< orphan*/  RETRO_DEVICE_KEYBOARD ; 
 int /*<<< orphan*/  handle_xkb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_keyboard_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_keymaps_translate_keysym_to_rk (unsigned int) ; 
 unsigned int input_unify_ev_key_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_key_state ; 
 int /*<<< orphan*/  video_driver_has_focus () ; 

__attribute__((used)) static void udev_handle_keyboard(void *data,
      const struct input_event *event, udev_input_device_t *dev)
{
#ifdef UDEV_XKB_HANDLING
   udev_input_t *udev = (udev_input_t*)data;
#endif
   unsigned keysym;

   switch (event->type)
   {
      case EV_KEY:
         keysym = input_unify_ev_key_code(event->code);
         if (event->value && video_driver_has_focus())
            BIT_SET(udev_key_state, keysym);
         else
            BIT_CLEAR(udev_key_state, keysym);

#ifdef UDEV_XKB_HANDLING
         if (udev->xkb_handling && handle_xkb(keysym, event->value) == 0)
            return;
#endif

         input_keyboard_event(event->value,
               input_keymaps_translate_keysym_to_rk(keysym),
               0, 0, RETRO_DEVICE_KEYBOARD);
         break;

      default:
         break;
   }
}