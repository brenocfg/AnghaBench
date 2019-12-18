#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct config_include_list {struct config_include_list* next; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  real_path ;
struct TYPE_6__ {scalar_t__ include_depth; int /*<<< orphan*/  path; struct config_include_list* includes; } ;
typedef  TYPE_1__ config_file_t ;
typedef  int /*<<< orphan*/  config_file_cb_t ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  add_child_list (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  config_file_free (TYPE_1__*) ; 
 scalar_t__ config_file_new_internal (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_pathname_resolve_relative (char*,int /*<<< orphan*/ ,char*,int) ; 
 char* getenv (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static void add_sub_conf(config_file_t *conf, char *path, config_file_cb_t *cb)
{
   char real_path[PATH_MAX_LENGTH];
   config_file_t         *sub_conf  = NULL;
   struct config_include_list *head = conf->includes;
   struct config_include_list *node = (struct config_include_list*)
      malloc(sizeof(*node));

   if (node)
   {
      node->next = NULL;
      /* Add include list */
      node->path = strdup(path);

      if (head)
      {
         while (head->next)
            head = head->next;

         head->next = node;
      }
      else
         conf->includes = node;
   }

   real_path[0] = '\0';

#ifdef _WIN32
   if (!string_is_empty(conf->path))
      fill_pathname_resolve_relative(real_path, conf->path,
            path, sizeof(real_path));
#else
#ifndef __CELLOS_LV2__
   if (*path == '~')
   {
      const char *home = getenv("HOME");
      strlcpy(real_path, home ? home : "", sizeof(real_path));
      strlcat(real_path, path + 1, sizeof(real_path));
   }
   else
#endif
      if (!string_is_empty(conf->path))
         fill_pathname_resolve_relative(real_path, conf->path,
               path, sizeof(real_path));
#endif

   sub_conf = (config_file_t*)
      config_file_new_internal(real_path, conf->include_depth + 1, cb);
   if (!sub_conf)
      return;

   /* Pilfer internal list. */
   add_child_list(conf, sub_conf);
   config_file_free(sub_conf);
}