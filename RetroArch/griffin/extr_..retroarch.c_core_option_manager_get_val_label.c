#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct core_option {size_t index; TYPE_2__* val_labels; } ;
struct TYPE_7__ {size_t size; int /*<<< orphan*/ * opts; } ;
typedef  TYPE_3__ core_option_manager_t ;
struct TYPE_6__ {TYPE_1__* elems; } ;
struct TYPE_5__ {char const* data; } ;

/* Variables and functions */

const char *core_option_manager_get_val_label(core_option_manager_t *opt, size_t idx)
{
   struct core_option *option = NULL;
   if (!opt)
      return NULL;
   if (idx >= opt->size)
      return NULL;
   option = (struct core_option*)&opt->opts[idx];
   return option->val_labels->elems[option->index].data;
}