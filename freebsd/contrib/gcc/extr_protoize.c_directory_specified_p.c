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
struct string_list {int /*<<< orphan*/  name; struct string_list* next; } ;

/* Variables and functions */
 scalar_t__ IS_DIR_SEPARATOR (char const) ; 
 struct string_list* directory_list ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
directory_specified_p (const char *name)
{
  struct string_list *p;

  for (p = directory_list; p; p = p->next)
    if (!strncmp (name, p->name, strlen (p->name))
	&& IS_DIR_SEPARATOR (name[strlen (p->name)]))
      {
	const char *q = name + strlen (p->name) + 1;

	/* If there are more slashes, it's in a subdir, so
	   this match doesn't count.  */
	while (*q++)
	  if (IS_DIR_SEPARATOR (*(q-1)))
	    goto lose;
	return 1;

      lose: ;
      }

  return 0;
}