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
struct android_app {int /*<<< orphan*/  mutex; int /*<<< orphan*/  unfocused; } ;

/* Variables and functions */
 scalar_t__ g_android ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool android_gfx_ctx_has_focus(void *data)
{
   bool                    focused = false;
   struct android_app *android_app = (struct android_app*)g_android;
   if (!android_app)
      return true;

   slock_lock(android_app->mutex);
   focused = !android_app->unfocused;
   slock_unlock(android_app->mutex);

   return focused;
}