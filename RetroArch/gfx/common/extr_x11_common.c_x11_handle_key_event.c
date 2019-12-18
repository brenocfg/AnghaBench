#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  keybuf ;
typedef  int /*<<< orphan*/  XIC ;
struct TYPE_7__ {unsigned int state; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_3__ xkey; } ;
typedef  TYPE_1__ XEvent ;
typedef  int /*<<< orphan*/  Status ;
typedef  scalar_t__ KeySym ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 unsigned int ControlMask ; 
 scalar_t__ KeyPress ; 
 unsigned int LockMask ; 
 unsigned int Mod1Mask ; 
 unsigned int Mod2Mask ; 
 unsigned int Mod4Mask ; 
 int /*<<< orphan*/  RETROKMOD_ALT ; 
 int /*<<< orphan*/  RETROKMOD_CAPSLOCK ; 
 int /*<<< orphan*/  RETROKMOD_CTRL ; 
 int /*<<< orphan*/  RETROKMOD_META ; 
 int /*<<< orphan*/  RETROKMOD_NUMLOCK ; 
 int /*<<< orphan*/  RETROKMOD_SHIFT ; 
 unsigned int RETROK_UNKNOWN ; 
 int /*<<< orphan*/  RETRO_DEVICE_KEYBOARD ; 
 unsigned int ShiftMask ; 
 scalar_t__ XK_A ; 
 scalar_t__ XK_Z ; 
 scalar_t__ XK_z ; 
 scalar_t__ XLookupKeysym (TYPE_3__*,int) ; 
 int XLookupString (TYPE_3__*,char*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int Xutf8LookupString (int /*<<< orphan*/ ,TYPE_3__*,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_keyboard_event (int,unsigned int,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int input_keymaps_translate_keysym_to_rk (unsigned int) ; 
 int utf8_conv_utf32 (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void x11_handle_key_event(unsigned keycode, XEvent *event, XIC ic, bool filter)
{
   int i;
   Status status;
   uint32_t chars[32];
   unsigned key   = 0;
   uint16_t mod   = 0;
   unsigned state = event->xkey.state;
   bool down      = event->type == KeyPress;
   int num        = 0;
   KeySym keysym  = 0;

   chars[0]       = '\0';

   /* this code generates the localized chars using keysyms */
   if (!filter)
   {
      if (down)
      {
         char keybuf[32];

         keybuf[0] = '\0';
#ifdef X_HAVE_UTF8_STRING
         status = 0;

         /* XwcLookupString doesn't seem to work. */
         num = Xutf8LookupString(ic, &event->xkey, keybuf,
               ARRAY_SIZE(keybuf), &keysym, &status);

         /* libc functions need UTF-8 locale to work properly,
          * which makes mbrtowc a bit impractical.
          *
          * Use custom UTF8 -> UTF-32 conversion. */
         num = utf8_conv_utf32(chars, ARRAY_SIZE(chars), keybuf, num);
#else
         (void)ic;
         num = XLookupString(&event->xkey, keybuf,
               sizeof(keybuf), &keysym, NULL); /* ASCII only. */
         for (i = 0; i < num; i++)
            chars[i] = keybuf[i] & 0x7f;
#endif
      }
      else
         keysym = XLookupKeysym(&event->xkey, (state & ShiftMask) || (state & LockMask));
   }

   /* We can't feed uppercase letters to the keycode translator. Seems like a bad idea
    * to feed it keysyms anyway, so here is a little hack... */
   if (keysym >= XK_A && keysym <= XK_Z)
       keysym += XK_z - XK_Z;

   /* Get the real keycode,
      that correctly ignores international layouts as windows code does. */
   key     = input_keymaps_translate_keysym_to_rk(keycode);

   if (state & ShiftMask)
      mod |= RETROKMOD_SHIFT;
   if (state & LockMask)
      mod |= RETROKMOD_CAPSLOCK;
   if (state & ControlMask)
      mod |= RETROKMOD_CTRL;
   if (state & Mod1Mask)
      mod |= RETROKMOD_ALT;
   if (state & Mod2Mask)
      mod |= RETROKMOD_NUMLOCK;
   if (state & Mod4Mask)
      mod |= RETROKMOD_META;

   input_keyboard_event(down, key, chars[0], mod, RETRO_DEVICE_KEYBOARD);

   for (i = 1; i < num; i++)
      input_keyboard_event(down, RETROK_UNKNOWN,
            chars[i], mod, RETRO_DEVICE_KEYBOARD);
}