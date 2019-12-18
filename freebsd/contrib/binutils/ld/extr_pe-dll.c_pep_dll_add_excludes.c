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
struct exclude_list_struct {int type; struct exclude_list_struct* next; void* string; } ;

/* Variables and functions */
 struct exclude_list_struct* excludes ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcpy (void*,char*) ; 
 int strlen (char*) ; 
 char* strtok (char*,char*) ; 
 void* xmalloc (int) ; 
 char* xstrdup (char const*) ; 

void
pe_dll_add_excludes (const char *new_excludes, const int type)
{
  char *local_copy;
  char *exclude_string;

  local_copy = xstrdup (new_excludes);

  exclude_string = strtok (local_copy, ",:");
  for (; exclude_string; exclude_string = strtok (NULL, ",:"))
    {
      struct exclude_list_struct *new_exclude;

      new_exclude = xmalloc (sizeof (struct exclude_list_struct));
      new_exclude->string = xmalloc (strlen (exclude_string) + 1);
      strcpy (new_exclude->string, exclude_string);
      new_exclude->type = type;
      new_exclude->next = excludes;
      excludes = new_exclude;
    }

  free (local_copy);
}