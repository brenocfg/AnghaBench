#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ctx_data; TYPE_1__* ctx_driver; } ;
typedef  TYPE_2__ gl_core_t ;
struct TYPE_3__ {int (* suppress_screensaver ) (scalar_t__,int) ;} ;

/* Variables and functions */
 int stub1 (scalar_t__,int) ; 

__attribute__((used)) static bool gl_core_suppress_screensaver(void *data, bool enable)
{
   bool enabled                = enable;
   gl_core_t         *gl       = (gl_core_t*)data;
   if (gl->ctx_data && gl->ctx_driver->suppress_screensaver)
      return gl->ctx_driver->suppress_screensaver(gl->ctx_data, enabled);
   return false;
}