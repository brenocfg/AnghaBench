#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {unsigned int size; TYPE_1__* elems; } ;
struct config_file_userdata {int /*<<< orphan*/  conf; int /*<<< orphan*/ * prefix; } ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ calloc (unsigned int,int) ; 
 scalar_t__ config_get_string (int /*<<< orphan*/ ,char*,char**) ; 
 int /*<<< orphan*/  fill_pathname_join_delim (char*,int /*<<< orphan*/ ,char const*,char,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (float*,float const*,int) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_split (char*,char*) ; 
 scalar_t__ strtod (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int config_userdata_get_float_array(void *userdata, const char *key_str,
      float **values, unsigned *out_num_values,
      const float *default_values, unsigned num_default_values)
{
   char key[2][256];
   struct config_file_userdata *usr = (struct config_file_userdata*)userdata;
   char *str = NULL;

   fill_pathname_join_delim(key[0], usr->prefix[0], key_str, '_', sizeof(key[0]));
   fill_pathname_join_delim(key[1], usr->prefix[1], key_str, '_', sizeof(key[1]));

   if (  config_get_string(usr->conf, key[0], &str) ||
         config_get_string(usr->conf, key[1], &str))
   {
      unsigned i;
      struct string_list *list = string_split(str, " ");
      *values = (float*)calloc(list->size, sizeof(float));
      for (i = 0; i < list->size; i++)
         (*values)[i] = (float)strtod(list->elems[i].data, NULL);
      *out_num_values = (unsigned)list->size;
      string_list_free(list);
      free(str);
      return true;
   }

   *values = (float*)calloc(num_default_values, sizeof(float));
   memcpy(*values, default_values, sizeof(float) * num_default_values);
   *out_num_values = num_default_values;
   return false;
}