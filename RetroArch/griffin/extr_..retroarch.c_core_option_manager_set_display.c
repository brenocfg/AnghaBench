#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t size; TYPE_1__* opts; } ;
typedef  TYPE_2__ core_option_manager_t ;
struct TYPE_4__ {char const* key; int visible; } ;

/* Variables and functions */
 scalar_t__ string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,char const*) ; 

__attribute__((used)) static void core_option_manager_set_display(core_option_manager_t *opt,
      const char *key, bool visible)
{
   size_t i;

   if (!opt || string_is_empty(key))
      return;

   for (i = 0; i < opt->size; i++)
   {
      if (string_is_empty(opt->opts[i].key))
         continue;

      if (string_is_equal(opt->opts[i].key, key))
      {
         opt->opts[i].visible = visible;
         return;
      }
   }
}