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
struct TYPE_3__ {int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__**) ; 
 TYPE_1__** menu_display_ctx_drivers ; 
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 

bool menu_display_driver_exists(const char *s)
{
   unsigned i;
   for (i = 0; i < ARRAY_SIZE(menu_display_ctx_drivers); i++)
   {
      if (string_is_equal(s, menu_display_ctx_drivers[i]->ident))
         return true;
   }

   return false;
}