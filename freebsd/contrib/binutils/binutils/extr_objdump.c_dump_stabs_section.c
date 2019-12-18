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
struct TYPE_3__ {char* section_name; char* string_section_name; scalar_t__ string_offset; } ;
typedef  TYPE_1__ stab_section_names ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  find_stabs_section ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strtab ; 

__attribute__((used)) static void
dump_stabs_section (bfd *abfd, char *stabsect_name, char *strsect_name)
{
  stab_section_names s;

  s.section_name = stabsect_name;
  s.string_section_name = strsect_name;
  s.string_offset = 0;

  bfd_map_over_sections (abfd, find_stabs_section, & s);

  free (strtab);
  strtab = NULL;
}