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
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  init_refcount ; 
 int /*<<< orphan*/  vcos_global_lock () ; 
 int /*<<< orphan*/  vcos_global_unlock () ; 
 int /*<<< orphan*/  vcos_platform_init () ; 

VCOS_STATUS_T vcos_init(void)
{
   VCOS_STATUS_T st = VCOS_SUCCESS;

   vcos_global_lock();

   if (init_refcount++ == 0)
      st = vcos_platform_init();

   vcos_global_unlock();

   return st;
}