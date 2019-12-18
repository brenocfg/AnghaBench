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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {scalar_t__ state; int modifier; scalar_t__ UTF16; int /*<<< orphan*/  scancode; } ;
typedef  TYPE_1__ KBDKeyEvent ;

/* Variables and functions */
 int KBD_WIIU_ALT ; 
 int KBD_WIIU_CAPS_LOCK ; 
 int KBD_WIIU_CTRL ; 
 int KBD_WIIU_NUM_LOCK ; 
 int KBD_WIIU_SCROLL_LOCK ; 
 int KBD_WIIU_SHIFT ; 
 int /*<<< orphan*/  RETROKMOD_ALT ; 
 int /*<<< orphan*/  RETROKMOD_CAPSLOCK ; 
 int /*<<< orphan*/  RETROKMOD_CTRL ; 
 int /*<<< orphan*/  RETROKMOD_NUMLOCK ; 
 int /*<<< orphan*/  RETROKMOD_SCROLLOCK ; 
 int /*<<< orphan*/  RETROKMOD_SHIFT ; 
 unsigned int RETROK_LAST ; 
 int /*<<< orphan*/  RETRO_DEVICE_KEYBOARD ; 
 int /*<<< orphan*/  input_keyboard_event (int,unsigned int,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int input_keymaps_translate_keysym_to_rk (int /*<<< orphan*/ ) ; 
 int* keyboardState ; 

void kb_key_callback(KBDKeyEvent *key)
{
   uint16_t mod        = 0;
   unsigned code       = 0;
   bool pressed        = false;

   if (key->state > 0)
      pressed = true;

   code                = input_keymaps_translate_keysym_to_rk(key->scancode);
   if (code < RETROK_LAST)
      keyboardState[code] = pressed;

   if (key->modifier & KBD_WIIU_SHIFT)
      mod |= RETROKMOD_SHIFT;

   if (key->modifier & KBD_WIIU_CTRL)
      mod |= RETROKMOD_CTRL;

   if (key->modifier & KBD_WIIU_ALT)
      mod |= RETROKMOD_ALT;

   if (key->modifier & KBD_WIIU_NUM_LOCK)
      mod |= RETROKMOD_NUMLOCK;

   if (key->modifier & KBD_WIIU_CAPS_LOCK)
      mod |= RETROKMOD_CAPSLOCK;

   if (key->modifier & KBD_WIIU_SCROLL_LOCK)
      mod |= RETROKMOD_SCROLLOCK;

   input_keyboard_event(pressed, code, (char)key->UTF16, mod,
         RETRO_DEVICE_KEYBOARD);
}