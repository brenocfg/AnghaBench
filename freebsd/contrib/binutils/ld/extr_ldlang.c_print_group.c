#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lang_output_section_statement_type ;
struct TYPE_5__ {int /*<<< orphan*/  head; } ;
struct TYPE_6__ {TYPE_1__ children; } ;
typedef  TYPE_2__ lang_group_statement_type ;
struct TYPE_7__ {int /*<<< orphan*/  map_file; } ;

/* Variables and functions */
 TYPE_4__ config ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_statement_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_group (lang_group_statement_type *s,
	     lang_output_section_statement_type *os)
{
  fprintf (config.map_file, "START GROUP\n");
  print_statement_list (s->children.head, os);
  fprintf (config.map_file, "END GROUP\n");
}