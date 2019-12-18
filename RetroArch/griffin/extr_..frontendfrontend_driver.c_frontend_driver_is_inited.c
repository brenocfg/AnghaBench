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
typedef  int /*<<< orphan*/  frontend_ctx_driver_t ;

/* Variables and functions */
 int /*<<< orphan*/ * frontend_get_ptr () ; 

bool frontend_driver_is_inited(void)
{
   frontend_ctx_driver_t *frontend = frontend_get_ptr();
   if (!frontend)
      return false;
   return true;
}