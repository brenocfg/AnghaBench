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
union string_list_elem_attr {int /*<<< orphan*/  i; } ;
struct retro_core_option_value {char* value; char* label; } ;
struct retro_core_option_definition {char* key; char* desc; char* info; char* default_value; struct retro_core_option_value* values; } ;
struct core_option {int visible; size_t default_index; size_t index; TYPE_3__* vals; void* key; TYPE_3__* val_labels; void* info; void* desc; } ;
struct TYPE_6__ {int /*<<< orphan*/ * conf; int /*<<< orphan*/ * opts; } ;
typedef  TYPE_2__ core_option_manager_t ;
typedef  int /*<<< orphan*/  config_file_t ;
struct TYPE_7__ {size_t size; TYPE_1__* elems; } ;
struct TYPE_5__ {char* data; } ;

/* Variables and functions */
 scalar_t__ config_get_string (int /*<<< orphan*/ *,void*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 int /*<<< orphan*/  string_list_append (TYPE_3__*,char*,union string_list_elem_attr) ; 
 void* string_list_new () ; 

__attribute__((used)) static bool core_option_manager_parse_option(
      core_option_manager_t *opt, size_t idx,
      const struct retro_core_option_definition *option_def,
      config_file_t *config_src)
{
   size_t i;
   union string_list_elem_attr attr;
   size_t num_vals                              = 0;
   char *config_val                             = NULL;
   struct core_option *option                   = (struct core_option*)&opt->opts[idx];
   const struct retro_core_option_value *values = option_def->values;

   /* All options are visible by default */
   option->visible = true;

   if (!string_is_empty(option_def->key))
      option->key             = strdup(option_def->key);

   if (!string_is_empty(option_def->desc))
      option->desc            = strdup(option_def->desc);

   if (!string_is_empty(option_def->info))
      option->info            = strdup(option_def->info);

   /* Get number of values */
   while (true)
   {
      if (!string_is_empty(values[num_vals].value))
         num_vals++;
      else
         break;
   }

   if (num_vals < 1)
      return false;

   /* Initialise string lists */
   attr.i             = 0;
   option->vals       = string_list_new();
   option->val_labels = string_list_new();

   if (!option->vals || !option->val_labels)
      return false;

   /* Initialse default value */
   option->default_index = 0;
   option->index         = 0;

   /* Extract value/label pairs */
   for (i = 0; i < num_vals; i++)
   {
      /* We know that 'value' is valid */
      string_list_append(option->vals, values[i].value, attr);

      /* Value 'label' may be NULL */
      if (!string_is_empty(values[i].label))
         string_list_append(option->val_labels, values[i].label, attr);
      else
         string_list_append(option->val_labels, values[i].value, attr);

      /* Check whether this value is the default setting */
      if (!string_is_empty(option_def->default_value))
      {
         if (string_is_equal(option_def->default_value, values[i].value))
         {
            option->default_index = i;
            option->index         = i;
         }
      }
   }

   /* Set current config value */
   if (config_get_string(config_src ? config_src : opt->conf, option->key, &config_val))
   {
      for (i = 0; i < option->vals->size; i++)
      {
         if (string_is_equal(option->vals->elems[i].data, config_val))
         {
            option->index = i;
            break;
         }
      }

      free(config_val);
   }

   return true;
}