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
 int /*<<< orphan*/  mmal_core_lock ; 
 scalar_t__ mmal_core_refcount ; 
 int /*<<< orphan*/  mmal_logging_deinit () ; 
 int /*<<< orphan*/  vcos_deinit () ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmal_core_deinit(void)
{
   vcos_mutex_lock(&mmal_core_lock);
   if (!mmal_core_refcount || --mmal_core_refcount)
   {
      vcos_mutex_unlock(&mmal_core_lock);
      return;
   }

   mmal_logging_deinit();
   vcos_mutex_unlock(&mmal_core_lock);
   vcos_deinit();
}