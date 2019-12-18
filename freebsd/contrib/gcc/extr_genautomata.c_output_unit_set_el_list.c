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
typedef  TYPE_2__* unit_set_el_t ;
struct TYPE_5__ {TYPE_1__* unit_decl; struct TYPE_5__* next_unit_set_el; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  output_description_file ; 

__attribute__((used)) static void
output_unit_set_el_list (unit_set_el_t list)
{
  unit_set_el_t el;

  for (el = list; el != NULL; el = el->next_unit_set_el)
    {
      if (el != list)
	fprintf (output_description_file, ", ");
      fprintf (output_description_file, "%s", el->unit_decl->name);
    }
}