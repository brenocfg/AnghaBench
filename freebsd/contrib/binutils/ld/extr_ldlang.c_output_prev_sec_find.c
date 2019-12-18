#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int constraint; TYPE_2__* bfd_section; struct TYPE_5__* prev; } ;
typedef  TYPE_1__ lang_output_section_statement_type ;
struct TYPE_6__ {int /*<<< orphan*/ * owner; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */

__attribute__((used)) static asection *
output_prev_sec_find (lang_output_section_statement_type *os)
{
  lang_output_section_statement_type *lookup;

  for (lookup = os->prev; lookup != NULL; lookup = lookup->prev)
    {
      if (lookup->constraint == -1)
	continue;

      if (lookup->bfd_section != NULL && lookup->bfd_section->owner != NULL)
	return lookup->bfd_section;
    }

  return NULL;
}