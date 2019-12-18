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
struct dependency {struct dependency* next; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 struct dependency* dep_chain ; 
 int /*<<< orphan*/ * dep_file ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

void
register_dependency (char *filename)
{
  struct dependency *dep;

  if (dep_file == NULL)
    return;

  for (dep = dep_chain; dep != NULL; dep = dep->next)
    {
      if (!strcmp (filename, dep->file))
	return;
    }

  dep = (struct dependency *) xmalloc (sizeof (struct dependency));
  dep->file = xstrdup (filename);
  dep->next = dep_chain;
  dep_chain = dep;
}