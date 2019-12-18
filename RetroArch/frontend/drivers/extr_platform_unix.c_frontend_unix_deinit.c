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
struct android_app {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  android_app_destroy (struct android_app*) ; 

__attribute__((used)) static void frontend_unix_deinit(void *data)
{
#ifdef ANDROID
   struct android_app *android_app = (struct android_app*)data;

   if (!android_app)
      return;

   android_app_destroy(android_app);
#endif
}