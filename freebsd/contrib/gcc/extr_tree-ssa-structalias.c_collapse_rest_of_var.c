#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* varinfo_t ;
struct TYPE_3__ {char* name; unsigned int id; scalar_t__ offset; scalar_t__ fullsize; scalar_t__ size; struct TYPE_3__* next; struct TYPE_3__* collapsed_to; } ;

/* Variables and functions */
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*,char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* get_varinfo (unsigned int) ; 

__attribute__((used)) static unsigned int
collapse_rest_of_var (unsigned int var)
{
  varinfo_t currvar = get_varinfo (var);
  varinfo_t field;

  for (field = currvar->next; field; field = field->next)
    {
      if (dump_file)
	fprintf (dump_file, "Type safety: Collapsing var %s into %s\n",
		 field->name, currvar->name);

      gcc_assert (!field->collapsed_to);
      field->collapsed_to = currvar;
    }

  currvar->next = NULL;
  currvar->size = currvar->fullsize - currvar->offset;

  return currvar->id;
}