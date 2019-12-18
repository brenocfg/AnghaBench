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
struct android_app {scalar_t__** analog_state; scalar_t__** hat_state; } ;

/* Variables and functions */
 unsigned int DEFAULT_MAX_PADS ; 
 unsigned int MAX_AXIS ; 
 scalar_t__ g_android ; 

__attribute__((used)) static void android_joypad_destroy(void)
{
   unsigned i, j;
   struct android_app *android_app = (struct android_app*)g_android;

   for (i = 0; i < DEFAULT_MAX_PADS; i++)
   {
      for (j = 0; j < 2; j++)
         android_app->hat_state[i][j]    = 0;
      for (j = 0; j < MAX_AXIS; j++)
         android_app->analog_state[i][j] = 0;
   }
}