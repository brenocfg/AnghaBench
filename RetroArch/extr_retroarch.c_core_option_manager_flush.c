#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct core_option {int /*<<< orphan*/  key; } ;
struct TYPE_9__ {size_t size; TYPE_3__* opts; } ;
typedef  TYPE_4__ core_option_manager_t ;
typedef  int /*<<< orphan*/  config_file_t ;
struct TYPE_8__ {size_t index; TYPE_2__* vals; } ;
struct TYPE_7__ {TYPE_1__* elems; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_set_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void core_option_manager_flush(
      config_file_t *conf,
      core_option_manager_t *opt,
      const char *path)
{
   size_t i;

   for (i = 0; i < opt->size; i++)
   {
      struct core_option *option = (struct core_option*)&opt->opts[i];

      if (option)
         config_set_string(conf, option->key,
               opt->opts[i].vals->elems[opt->opts[i].index].data);
   }
}