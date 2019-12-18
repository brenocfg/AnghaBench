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
struct config_entry_list {char* key; void* value; } ;
struct TYPE_4__ {scalar_t__ include_depth; } ;
typedef  TYPE_1__ config_file_t ;
typedef  int /*<<< orphan*/  config_file_cb_t ;

/* Variables and functions */
 scalar_t__ MAX_INCLUDE_DEPTH ; 
 int STRLEN_CONST (char*) ; 
 int /*<<< orphan*/  add_sub_conf (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 void* extract_value (char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isgraph (int) ; 
 scalar_t__ isspace (int) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ realloc (char*,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 char* strip_comment (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static bool parse_line(config_file_t *conf,
      struct config_entry_list *list, char *line, config_file_cb_t *cb)
{
   char *key       = NULL;
   char *key_tmp   = NULL;
   size_t cur_size = 8;
   size_t idx      = 0;
   char *comment   = strip_comment(line);

   /* Starting line with #include includes config files. */
   if (comment == line)
   {
      comment++;
      if (strstr(comment, "include ") == comment)
      {
         char *include_line = comment + STRLEN_CONST("include ");
         char *path         = extract_value(include_line, false);

         if (!path)
            return false;

         if (conf->include_depth >= MAX_INCLUDE_DEPTH)
            fprintf(stderr, "!!! #include depth exceeded for config. Might be a cycle.\n");
         else
            add_sub_conf(conf, path, cb);
         free(path);
      }
   }

   /* Skips to first character. */
   while (isspace((int)*line))
      line++;

   key             = (char*)malloc(9);

   while (isgraph((int)*line))
   {
      if (idx == cur_size)
      {
         cur_size *= 2;
         key_tmp   = (char*)realloc(key, cur_size + 1);

         if (!key_tmp)
         {
            free(key);
            return false;
         }

         key = key_tmp;
      }

      key[idx++] = *line++;
   }
   key[idx]      = '\0';
   list->key     = key;

   list->value   = extract_value(line, true);

   if (!list->value)
   {
      list->key = NULL;
      free(key);
      return false;
   }

   return true;
}