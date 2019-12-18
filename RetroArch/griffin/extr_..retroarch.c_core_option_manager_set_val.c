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
struct core_option {size_t index; TYPE_1__* vals; } ;
struct TYPE_5__ {size_t size; int updated; int /*<<< orphan*/ * opts; } ;
typedef  TYPE_2__ core_option_manager_t ;
struct TYPE_4__ {size_t size; } ;

/* Variables and functions */

void core_option_manager_set_val(core_option_manager_t *opt,
      size_t idx, size_t val_idx)
{
   struct core_option *option= NULL;

   if (!opt)
      return;
   if (idx >= opt->size)
      return;

   option        = (struct core_option*)&opt->opts[idx];
   option->index = val_idx % option->vals->size;

   opt->updated  = true;
}