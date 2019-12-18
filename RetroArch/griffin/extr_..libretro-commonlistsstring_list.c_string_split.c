#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
union string_list_elem_attr {scalar_t__ i; } ;
struct string_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char const*,union string_list_elem_attr) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_list_new () ; 
 char* strtok_r (char*,char const*,char**) ; 

struct string_list *string_split(const char *str, const char *delim)
{
   char *save      = NULL;
   char *copy      = NULL;
   const char *tmp = NULL;
   struct string_list *list = string_list_new();

   if (!list)
      goto error;

   copy = strdup(str);
   if (!copy)
      goto error;

   tmp = strtok_r(copy, delim, &save);
   while (tmp)
   {
      union string_list_elem_attr attr;

      attr.i = 0;

      if (!string_list_append(list, tmp, attr))
         goto error;

      tmp = strtok_r(NULL, delim, &save);
   }

   free(copy);
   return list;

error:
   string_list_free(list);
   free(copy);
   return NULL;
}