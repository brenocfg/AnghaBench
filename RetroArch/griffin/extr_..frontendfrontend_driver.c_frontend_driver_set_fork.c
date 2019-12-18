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
struct TYPE_3__ {int (* set_fork ) (int) ;} ;
typedef  TYPE_1__ frontend_ctx_driver_t ;
typedef  enum frontend_fork { ____Placeholder_frontend_fork } frontend_fork ;

/* Variables and functions */
 int /*<<< orphan*/  frontend_driver_has_fork () ; 
 TYPE_1__* frontend_get_ptr () ; 
 int stub1 (int) ; 

bool frontend_driver_set_fork(enum frontend_fork fork_mode)
{
   frontend_ctx_driver_t *frontend = frontend_get_ptr();

   if (!frontend_driver_has_fork())
      return false;
   return frontend->set_fork(fork_mode);
}