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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_free_mem ) () ;} ;
typedef  TYPE_1__ frontend_ctx_driver_t ;

/* Variables and functions */
 TYPE_1__* frontend_get_ptr () ; 
 int /*<<< orphan*/  stub1 () ; 

uint64_t frontend_driver_get_free_memory(void)
{
   frontend_ctx_driver_t *frontend = frontend_get_ptr();
   if (!frontend || !frontend->get_free_mem)
      return 0;
   return frontend->get_free_mem();
}