#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int* state; TYPE_1__* joypad; } ;
typedef  TYPE_2__ linuxraw_input_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* poll ) () ;} ;

/* Variables and functions */
 int KEY_C ; 
 size_t KEY_LEFTCTRL ; 
 size_t KEY_RIGHTCTRL ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void linuxraw_input_poll(void *data)
{
   uint8_t c;
   linuxraw_input_t *linuxraw = (linuxraw_input_t*)data;

   while (read(STDIN_FILENO, &c, 1) > 0)
   {
      bool pressed;
      uint16_t t;

      if (c == KEY_C && (linuxraw->state[KEY_LEFTCTRL] || linuxraw->state[KEY_RIGHTCTRL]))
         kill(getpid(), SIGINT);

      pressed = !(c & 0x80);
      c &= ~0x80;

      /* ignore extended scancodes */
      if (!c)
         read(STDIN_FILENO, &t, 2);
      else
         linuxraw->state[c] = pressed;
   }

   if (linuxraw->joypad)
      linuxraw->joypad->poll();
}