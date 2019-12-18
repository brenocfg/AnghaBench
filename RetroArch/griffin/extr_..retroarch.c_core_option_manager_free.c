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
struct TYPE_4__ {size_t size; struct TYPE_4__* opts; scalar_t__ conf; int /*<<< orphan*/ * vals; struct TYPE_4__* key; struct TYPE_4__* info; struct TYPE_4__* desc; int /*<<< orphan*/ * val_labels; } ;
typedef  TYPE_1__ core_option_manager_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_file_free (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  string_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void core_option_manager_free(core_option_manager_t *opt)
{
   size_t i;

   if (!opt)
      return;

   for (i = 0; i < opt->size; i++)
   {
      if (opt->opts[i].desc)
         free(opt->opts[i].desc);
      if (opt->opts[i].info)
         free(opt->opts[i].info);
      if (opt->opts[i].key)
         free(opt->opts[i].key);

      if (opt->opts[i].vals)
         string_list_free(opt->opts[i].vals);
      if (opt->opts[i].val_labels)
         string_list_free(opt->opts[i].val_labels);

      opt->opts[i].desc = NULL;
      opt->opts[i].info = NULL;
      opt->opts[i].key  = NULL;
      opt->opts[i].vals = NULL;
   }

   if (opt->conf)
      config_file_free(opt->conf);
   free(opt->opts);
   free(opt);
}