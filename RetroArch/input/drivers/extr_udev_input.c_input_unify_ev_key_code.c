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

/* Variables and functions */
#define  KEY_BACK 129 
 int KEY_BACKSPACE ; 
 int KEY_ENTER ; 
#define  KEY_OK 128 

__attribute__((used)) static unsigned input_unify_ev_key_code(unsigned code)
{
   /* input_keymaps_translate_keysym_to_rk does not support the case
      where multiple keysyms translate to the same RETROK_* code,
      so unify remote control keysyms to keyboard keysyms here.  */
   switch (code)
   {
      case KEY_OK:
         return KEY_ENTER;
      case KEY_BACK:
         return KEY_BACKSPACE;
      default:
         return code;
   }
}