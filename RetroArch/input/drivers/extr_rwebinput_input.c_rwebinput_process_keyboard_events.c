#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  char uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {char* key; scalar_t__ code; scalar_t__ metaKey; scalar_t__ shiftKey; scalar_t__ altKey; scalar_t__ ctrlKey; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_3__ event; } ;
typedef  TYPE_1__ rwebinput_keyboard_event_t ;
struct TYPE_7__ {int* keys; } ;
typedef  TYPE_2__ rwebinput_input_t ;
typedef  TYPE_3__ EmscriptenKeyboardEvent ;

/* Variables and functions */
 scalar_t__ EMSCRIPTEN_EVENT_KEYDOWN ; 
 int /*<<< orphan*/  RETROKMOD_ALT ; 
 int /*<<< orphan*/  RETROKMOD_CTRL ; 
 int /*<<< orphan*/  RETROKMOD_META ; 
 int /*<<< orphan*/  RETROKMOD_SHIFT ; 
 unsigned int RETROK_BACKSPACE ; 
 unsigned int RETROK_KP_ENTER ; 
 unsigned int RETROK_LAST ; 
 unsigned int RETROK_RETURN ; 
 unsigned int RETROK_TAB ; 
 int /*<<< orphan*/  RETRO_DEVICE_KEYBOARD ; 
 char encoding_crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_keyboard_event (int,unsigned int,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int input_keymaps_translate_keysym_to_rk (char) ; 
 int /*<<< orphan*/  strnlen (scalar_t__,int) ; 
 char utf8_walk (char const**) ; 
 int utf8len (char*) ; 

__attribute__((used)) static void rwebinput_process_keyboard_events(rwebinput_input_t *rwebinput,
   rwebinput_keyboard_event_t *event)
{
   uint32_t keycode;
   unsigned translated_keycode;
   uint32_t character = 0;
   uint16_t mod = 0;
   const EmscriptenKeyboardEvent *key_event = &event->event;
   bool keydown = event->type == EMSCRIPTEN_EVENT_KEYDOWN;

   /* a printable key: populate character field */
   if (utf8len(key_event->key) == 1)
   {
      const char *key_ptr = &key_event->key[0];
      character = utf8_walk(&key_ptr);
   }

   if (key_event->ctrlKey)
      mod |= RETROKMOD_CTRL;
   if (key_event->altKey)
      mod |= RETROKMOD_ALT;
   if (key_event->shiftKey)
      mod |= RETROKMOD_SHIFT;
   if (key_event->metaKey)
      mod |= RETROKMOD_META;

   keycode = encoding_crc32(0, (const uint8_t *)key_event->code,
      strnlen(key_event->code, sizeof(key_event->code)));
   translated_keycode = input_keymaps_translate_keysym_to_rk(keycode);

   if (translated_keycode == RETROK_BACKSPACE)
      character = '\b';
   else if (translated_keycode == RETROK_RETURN ||
            translated_keycode == RETROK_KP_ENTER)
      character = '\n';
   else if (translated_keycode == RETROK_TAB)
      character = '\t';

   input_keyboard_event(keydown, translated_keycode, character, mod,
      RETRO_DEVICE_KEYBOARD);

   if (translated_keycode < RETROK_LAST)
   {
      rwebinput->keys[translated_keycode] = keydown;
   }
}