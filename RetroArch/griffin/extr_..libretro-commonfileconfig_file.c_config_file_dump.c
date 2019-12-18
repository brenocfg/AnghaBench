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
struct config_include_list {char* path; struct config_include_list* next; } ;
struct config_entry_list {char* key; char* value; struct config_entry_list* next; int /*<<< orphan*/  readonly; } ;
struct TYPE_3__ {struct config_entry_list* entries; struct config_include_list* includes; } ;
typedef  TYPE_1__ config_file_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  config_sort_compare_func ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 struct config_entry_list* merge_sort_linked_list (struct config_entry_list*,int /*<<< orphan*/ ) ; 

void config_file_dump(config_file_t *conf, FILE *file, bool sort)
{
   struct config_entry_list       *list = NULL;
   struct config_include_list *includes = conf->includes;

   while (includes)
   {
      fprintf(file, "#include \"%s\"\n", includes->path);
      includes = includes->next;
   }

   if (sort)
      list = merge_sort_linked_list((struct config_entry_list*)
            conf->entries, config_sort_compare_func);
   else
      list = (struct config_entry_list*)conf->entries;

   conf->entries = list;

   while (list)
   {
      if (!list->readonly && list->key)
         fprintf(file, "%s = \"%s\"\n", list->key, list->value);
      list = list->next;
   }
}