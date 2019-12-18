#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* pattern_set_el_t ;
struct TYPE_5__ {int units_num; TYPE_1__** unit_decls; struct TYPE_5__* next_pattern_set_el; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  output_description_file ; 

__attribute__((used)) static void
output_pattern_set_el_list (pattern_set_el_t list)
{
  pattern_set_el_t el;
  int i;

  for (el = list; el != NULL; el = el->next_pattern_set_el)
    {
      if (el != list)
	fprintf (output_description_file, ", ");
      for (i = 0; i < el->units_num; i++)
	fprintf (output_description_file, (i == 0 ? "%s" : " %s"),
		 el->unit_decls [i]->name);
    }
}