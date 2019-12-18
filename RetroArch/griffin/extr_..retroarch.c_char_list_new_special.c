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
struct string_list {int dummy; } ;
typedef  enum string_list_type { ____Placeholder_string_list_type } string_list_type ;

/* Variables and functions */
 scalar_t__ calloc (unsigned int,int) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 int /*<<< orphan*/  string_list_join_concat (char*,unsigned int,struct string_list*,char*) ; 
 struct string_list* string_list_new_special (int,void*,unsigned int*,size_t*) ; 

const char *char_list_new_special(enum string_list_type type, void *data)
{
   unsigned len = 0;
   size_t list_size;
   struct string_list *s = string_list_new_special(type, data, &len, &list_size);
   char         *options = (len > 0) ? (char*)calloc(len, sizeof(char)): NULL;

   if (options && s)
      string_list_join_concat(options, len, s, "|");

   string_list_free(s);
   s = NULL;

   return options;
}