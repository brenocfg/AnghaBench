#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct wildcard_list {TYPE_1__ spec; } ;
struct TYPE_7__ {int /*<<< orphan*/ * found_section; int /*<<< orphan*/  multiple_sections_found; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ section_iterator_callback_data ;
struct TYPE_8__ {int /*<<< orphan*/  the_bfd; } ;
typedef  TYPE_3__ lang_input_statement_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  bfd_get_section_by_name_if (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  section_iterator_callback ; 

__attribute__((used)) static asection *
find_section (lang_input_statement_type *file,
	      struct wildcard_list *sec,
	      bfd_boolean *multiple_sections_found)
{
  section_iterator_callback_data cb_data = { NULL, FALSE };

  bfd_get_section_by_name_if (file->the_bfd, sec->spec.name,
			      section_iterator_callback, &cb_data);
  *multiple_sections_found = cb_data.multiple_sections_found;
  return cb_data.found_section;
}