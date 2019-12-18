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
 scalar_t__ init_refcount ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_global_lock () ; 
 int /*<<< orphan*/  vcos_global_unlock () ; 
 int /*<<< orphan*/  vcos_platform_deinit () ; 

void vcos_deinit(void)
{
   vcos_global_lock();

   vcos_assert(init_refcount > 0);

   if (init_refcount > 0 && --init_refcount == 0)
      vcos_platform_deinit();

   vcos_global_unlock();
}