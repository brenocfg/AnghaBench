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
struct TYPE_3__ {int* keys; } ;
typedef  TYPE_1__ rwebinput_input_t ;

/* Variables and functions */
 int RETROK_LAST ; 

__attribute__((used)) static bool rwebinput_key_pressed(rwebinput_input_t *rwebinput, int key)
{
   if (key >= RETROK_LAST)
      return false;

   return rwebinput->keys[key];
}