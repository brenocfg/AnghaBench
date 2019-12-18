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
struct android_app {int /*<<< orphan*/ ** analog_state; int /*<<< orphan*/ ** hat_state; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** analog_state; int /*<<< orphan*/ ** hat_state; } ;
typedef  TYPE_1__ android_input_t ;

/* Variables and functions */
 unsigned int DEFAULT_MAX_PADS ; 
 unsigned int MAX_AXIS ; 
 scalar_t__ g_android ; 

__attribute__((used)) static void android_input_poll_memcpy(android_input_t *android)
{
   unsigned i, j;
   struct android_app *android_app = (struct android_app*)g_android;

   for (i = 0; i < DEFAULT_MAX_PADS; i++)
   {
      for (j = 0; j < 2; j++)
         android_app->hat_state[i][j]    = android->hat_state[i][j];
      for (j = 0; j < MAX_AXIS; j++)
         android_app->analog_state[i][j] = android->analog_state[i][j];
   }
}