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
struct TYPE_4__ {char const* old_name; char const* new_name; scalar_t__ flags; struct TYPE_4__* next; } ;
typedef  TYPE_1__ section_rename ;
typedef  scalar_t__ flagword ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* section_rename_list ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 TYPE_1__* xmalloc (int) ; 

__attribute__((used)) static void
add_section_rename (const char * old_name, const char * new_name,
		    flagword flags)
{
  section_rename * rename;

  /* Check for conflicts first.  */
  for (rename = section_rename_list; rename != NULL; rename = rename->next)
    if (strcmp (rename->old_name, old_name) == 0)
      {
	/* Silently ignore duplicate definitions.  */
	if (strcmp (rename->new_name, new_name) == 0
	    && rename->flags == flags)
	  return;

	fatal (_("Multiple renames of section %s"), old_name);
      }

  rename = xmalloc (sizeof (* rename));

  rename->old_name = old_name;
  rename->new_name = new_name;
  rename->flags    = flags;
  rename->next     = section_rename_list;

  section_rename_list = rename;
}