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
struct unique_sections {struct unique_sections* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct unique_sections* unique_section_list ; 
 struct unique_sections* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

void
lang_add_unique (const char *name)
{
  struct unique_sections *ent;

  for (ent = unique_section_list; ent; ent = ent->next)
    if (strcmp (ent->name, name) == 0)
      return;

  ent = xmalloc (sizeof *ent);
  ent->name = xstrdup (name);
  ent->next = unique_section_list;
  unique_section_list = ent;
}