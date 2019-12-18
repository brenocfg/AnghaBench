#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ident; } ;
typedef  TYPE_1__ frontend_ctx_driver_t ;

/* Variables and functions */
 TYPE_1__** frontend_ctx_drivers ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char const*) ; 

frontend_ctx_driver_t *frontend_ctx_find_driver(const char *ident)
{
   unsigned i;

   for (i = 0; frontend_ctx_drivers[i]; i++)
   {
      if (string_is_equal(frontend_ctx_drivers[i]->ident, ident))
         return frontend_ctx_drivers[i];
   }

   return NULL;
}