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
struct string_list {scalar_t__ size; TYPE_1__* elems; } ;
typedef  int /*<<< orphan*/  elem0_path ;
struct TYPE_2__ {char const* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NOT_AVAILABLE ; 
 char const* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_basename (char*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_split (char const*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static int action_get_title_generic(char *s, size_t len, const char *path,
      const char *text)
{
   struct string_list *list_path    = NULL;

   if (!string_is_empty(path))
      list_path = string_split(path, "|");

   if (list_path)
   {
      char elem0_path[255];

      elem0_path[0] = '\0';

      if (list_path->size > 0)
         strlcpy(elem0_path, list_path->elems[0].data, sizeof(elem0_path));
      string_list_free(list_path);
      strlcpy(s, text, len);

      if (!string_is_empty(elem0_path))
      {
         strlcat(s, "- ", len);
         strlcat(s, path_basename(elem0_path), len);
      }
   }
   else
      strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NOT_AVAILABLE), len);

   return 0;
}