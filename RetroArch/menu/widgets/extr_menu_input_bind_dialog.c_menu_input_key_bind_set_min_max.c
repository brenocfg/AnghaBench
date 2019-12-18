#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
typedef  TYPE_1__ menu_input_ctx_bind_limits_t ;
struct TYPE_5__ {int /*<<< orphan*/  last; int /*<<< orphan*/  begin; } ;

/* Variables and functions */
 TYPE_3__ menu_input_binds ; 

bool menu_input_key_bind_set_min_max(menu_input_ctx_bind_limits_t *lim)
{
   if (!lim)
      return false;

   menu_input_binds.begin = lim->min;
   menu_input_binds.last  = lim->max;

   return true;
}