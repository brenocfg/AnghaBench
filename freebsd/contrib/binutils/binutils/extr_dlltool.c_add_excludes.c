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
struct string_list {char* string; struct string_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 struct string_list* excludes ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  inform (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int strlen (char*) ; 
 char* strtok (char*,char*) ; 
 scalar_t__ xmalloc (int) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static void
add_excludes (const char *new_excludes)
{
  char *local_copy;
  char *exclude_string;

  local_copy = xstrdup (new_excludes);

  exclude_string = strtok (local_copy, ",:");
  for (; exclude_string; exclude_string = strtok (NULL, ",:"))
    {
      struct string_list *new_exclude;

      new_exclude = ((struct string_list *)
		     xmalloc (sizeof (struct string_list)));
      new_exclude->string = (char *) xmalloc (strlen (exclude_string) + 2);
      /* Don't add a leading underscore for fastcall symbols.  */
      if (*exclude_string == '@')
	sprintf (new_exclude->string, "%s", exclude_string);
      else
	sprintf (new_exclude->string, "_%s", exclude_string);
      new_exclude->next = excludes;
      excludes = new_exclude;

      /* xgettext:c-format */
      inform (_("Excluding symbol: %s"), exclude_string);
    }

  free (local_copy);
}