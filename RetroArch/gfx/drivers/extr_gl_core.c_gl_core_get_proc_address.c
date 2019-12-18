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
typedef  int /*<<< orphan*/ * retro_proc_address_t ;
struct TYPE_4__ {TYPE_1__* ctx_driver; } ;
typedef  TYPE_2__ gl_core_t ;
struct TYPE_3__ {int /*<<< orphan*/ * (* get_proc_address ) (char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (char const*) ; 

__attribute__((used)) static retro_proc_address_t gl_core_get_proc_address(
      void *data, const char *sym)
{
   gl_core_t *gl = (gl_core_t*)data;
   if (gl && gl->ctx_driver->get_proc_address)
      return gl->ctx_driver->get_proc_address(sym);

   return NULL;
}