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
typedef  int /*<<< orphan*/  screen_event_t ;
struct TYPE_3__ {int /*<<< orphan*/  keyboard_state; } ;
typedef  TYPE_1__ qnx_input_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_CLEAR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BIT_SET (int /*<<< orphan*/ ,int) ; 
 int KEY_DOWN ; 
 int KEY_REPEAT ; 
 int /*<<< orphan*/  RETRO_DEVICE_KEYBOARD ; 
 int /*<<< orphan*/  SCREEN_PROPERTY_KEY_CAP ; 
 int /*<<< orphan*/  SCREEN_PROPERTY_KEY_FLAGS ; 
 int /*<<< orphan*/  SCREEN_PROPERTY_KEY_MODIFIERS ; 
 int /*<<< orphan*/  input_keyboard_event (int,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned int input_keymaps_translate_keysym_to_rk (int) ; 
 int /*<<< orphan*/  screen_get_event_property_iv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void qnx_process_keyboard_event(
      qnx_input_t *qnx,
      screen_event_t event, int type)
{
    // Get key properties from screen event
    int flags = 0;
    screen_get_event_property_iv(event, SCREEN_PROPERTY_KEY_FLAGS, &flags);

    int cap = 0;
    screen_get_event_property_iv(event, SCREEN_PROPERTY_KEY_CAP, &cap);

    int mod = 0;
    screen_get_event_property_iv(event, SCREEN_PROPERTY_KEY_MODIFIERS, &mod);

    // Calculate state
    unsigned keycode = input_keymaps_translate_keysym_to_rk(cap);
    bool keydown = flags & KEY_DOWN;
    bool keyrepeat = flags & KEY_REPEAT;

    // Fire keyboard event
    if(!keyrepeat)
    {
        input_keyboard_event(keydown, keycode, 0, mod, RETRO_DEVICE_KEYBOARD);
    }

    // Apply keyboard state
    if(keydown && !keyrepeat)
    {
       BIT_SET(qnx->keyboard_state, cap);
    }
    else if(!keydown && !keyrepeat)
    {
       BIT_CLEAR(qnx->keyboard_state, cap);
    }
}