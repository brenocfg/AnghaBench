#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct retro_core_option_definition {TYPE_1__* values; scalar_t__ desc; scalar_t__ key; } ;
struct core_option {int dummy; } ;
struct TYPE_7__ {size_t size; struct core_option* opts; int /*<<< orphan*/  conf_path; void* conf; } ;
typedef  TYPE_2__ core_option_manager_t ;
typedef  int /*<<< orphan*/  config_file_t ;
struct TYPE_6__ {scalar_t__ value; } ;

/* Variables and functions */
 scalar_t__ calloc (size_t,int) ; 
 int /*<<< orphan*/  config_file_free (int /*<<< orphan*/ *) ; 
 void* config_file_new_alloc () ; 
 void* config_file_new_from_path_to_string (char const*) ; 
 int /*<<< orphan*/  core_option_manager_free (TYPE_2__*) ; 
 int /*<<< orphan*/  core_option_manager_parse_option (TYPE_2__*,size_t,struct retro_core_option_definition const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static core_option_manager_t *core_option_manager_new(
      const char *conf_path, const char *src_conf_path,
      const struct retro_core_option_definition *option_defs)
{
   const struct retro_core_option_definition *option_def;
   size_t size                       = 0;
   core_option_manager_t *opt        = (core_option_manager_t*)
      calloc(1, sizeof(*opt));
   config_file_t *config_src         = NULL;

   if (!opt)
      return NULL;

   if (!string_is_empty(conf_path))
      if (!(opt->conf = config_file_new_from_path_to_string(conf_path)))
         if (!(opt->conf = config_file_new_alloc()))
            goto error;

   strlcpy(opt->conf_path, conf_path, sizeof(opt->conf_path));

   /* Load source config file, if required */
   if (!string_is_empty(src_conf_path))
      config_src = config_file_new_from_path_to_string(src_conf_path);

   /* Note: 'option_def->info == NULL' is valid */
   for (option_def = option_defs;
        option_def->key && option_def->desc && option_def->values[0].value;
        option_def++)
      size++;

   if (size == 0)
      goto error;

   opt->opts = (struct core_option*)calloc(size, sizeof(*opt->opts));
   if (!opt->opts)
      goto error;

   opt->size = size;
   size      = 0;

   /* Note: 'option_def->info == NULL' is valid */
   for (option_def = option_defs;
        option_def->key && option_def->desc && option_def->values[0].value;
        size++, option_def++)
   {
      if (!core_option_manager_parse_option(opt, size, option_def, config_src))
         goto error;
   }

   if (config_src)
      config_file_free(config_src);

   return opt;

error:
   if (config_src)
      config_file_free(config_src);
   core_option_manager_free(opt);
   return NULL;
}